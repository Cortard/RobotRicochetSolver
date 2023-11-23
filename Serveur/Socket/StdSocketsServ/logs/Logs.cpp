#include "Logs.h"

std::mutex Logs::mutex;
std::ofstream Logs::file;

bool Logs::openLogs()
{
    Logs::file = std::ofstream(LOG_PATH);
    return file.is_open();
}

bool Logs::write(const std::string &msg, int level)
{
    std::unique_lock<std::mutex> lock(mutex);
    if(!Logs::file.is_open() && ! openLogs()) return false ;

    time_t now = time(nullptr);
    std::string dt = ctime(&now);
    dt = dt.substr(0, dt.length() - 1);
    Logs::file<<dt<<": ";
    Logs::file<<msg;
    Logs::file<<" |"<<level;
    Logs::file<<std::endl;
    lock.unlock();

    return true;
}

void Logs::close()
{
    std::unique_lock<std::mutex> lock(mutex);
    Logs::file.close();
}

