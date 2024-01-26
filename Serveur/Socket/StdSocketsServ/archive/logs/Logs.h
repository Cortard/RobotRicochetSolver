#ifndef STDSOCKETSSERVER_LOGS_H
#define STDSOCKETSSERVER_LOGS_H

#include <fstream>
#include <ctime>
#include <mutex>
#include "../../configue.h"

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DETAILS 3
#define LOG_LEVEL_VERBOSE 4
#define LOG_LEVEL_DEBUG 5



class Logs {
private:
    static std::mutex mutex;
    static std::ofstream file;
    static bool openLogs();

public:
    static bool write(const std::string& msg, int level);
    static void close();
};


#endif //STDSOCKETSSERVER_LOGS_H
