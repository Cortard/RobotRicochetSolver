#ifndef RICOCHETSOCKETSSERVER_LOGS_H
#define RICOCHETSOCKETSSERVER_LOGS_H

#include <fstream>
#include <ctime>
#include <mutex>

#include "../config.h"

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DETAILS 3
#define LOG_LEVEL_VERBOSE 4
#define LOG_LEVEL_DEBUG 5

class Logs {
public:
    static bool write(const std::string& message, int level);
    static void close();

private:
    static std::mutex mutex;
    static std::ofstream file;
    static int openLogs();
    static std::string getTime();
};


#endif //RICOCHETSOCKETSSERVER_LOGS_H
