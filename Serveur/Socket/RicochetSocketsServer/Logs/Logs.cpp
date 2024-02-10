#include <iostream>
#include "Logs.h"

std::mutex Logs::mutex;
std::ofstream Logs::file;

bool Logs::write(const std::string& message, int level) {
    #if DEBUG_OUTPUT!=1
        if (level == LOG_LEVEL_DEBUG) return true;
    #endif
    #if LOG_IN_FILE==1
        std::unique_lock<std::mutex> lock(mutex);
        if (!Logs::file.is_open() && !openLogs()) return false;

        Logs::file << getTime() << ": ";
        Logs::file << message;
        Logs::file << " |" << level;
        Logs::file << std::endl;
        lock.unlock();
    #endif
    #if LOG_IN_CONSOLE==1
        std::cout << getTime() << ": ";
        std::cout << message;
        std::cout << " |" << level;
        std::cout << std::endl;
    #endif

    return true;

}

void Logs::close() {
    std::unique_lock<std::mutex> lock(mutex);
    Logs::file.close();
}

int Logs::openLogs() {
    Logs::file = std::ofstream(LOG_PATH);
    return file.is_open();
}

std::string Logs::getTime() {
    time_t now = time(nullptr);
    std::string dt = ctime(&now);
    dt = dt.substr(0, dt.length() - 1);
    return dt;
}