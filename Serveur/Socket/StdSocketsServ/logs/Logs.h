#ifndef STDSOCKETSSERVER_LOGS_H
#define STDSOCKETSSERVER_LOGS_H

#include <fstream>
#include <ctime>
#include "../devMode.h"

#if DEV_MODE==1
    #define LOG_PATH "./logs.txt"
#else
    #define LOG_PATH "/home/ricochet/logs.txt"
#endif

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DETAILS 3
#define LOG_LEVEL_VERBOSE 4
#define LOG_LEVEL_DEBUG 5



class Logs {
private:
    static std::ofstream file;
    static bool openLogs();

public:
    static bool write(const std::string& msg, int level);
    static void close();
};


#endif //STDSOCKETSSERVER_LOGS_H
