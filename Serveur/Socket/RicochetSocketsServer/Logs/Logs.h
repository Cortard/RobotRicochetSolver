#ifndef RICOCHETSOCKETSSERVER_LOGS_H
#define RICOCHETSOCKETSSERVER_LOGS_H

#include <fstream>
#include <ctime>
#include <mutex>

#include "../config.h"

/**
 * @brief The level of the logs
 * @details The higher the level, the more detailed the logs are
 */
#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DETAILS 3
#define LOG_LEVEL_VERBOSE 4
#define LOG_LEVEL_DEBUG 5

/**
 * @brief Class to write logs to a file and/or console
 */
class Logs {
public:
    /**
     * @brief Write a message to the logs, check if the file is open and try to open it if it's not
     * @param message The message to write to the logs
     * @param level The level of the logs
     * @return 0 if success, -1 if error
     * @note The message is written : [time]: [message] |[level]
     */
    static bool write(const std::string& message, int level);
    /**
     * @brief Close the logs file, should be called at the end of the program
     */
    static void close();

private:
    /**
     * @brief Mutex to avoid conflicts when writing to the logs file

     */
    static std::mutex mutex;

    /**
     * @brief File to write the logs to, opened in openLogs()
     */
    static std::ofstream file;

    /**
     * @brief Open the logs file
     * @return 0 if success, -1 if error
     */
    static int openLogs();

    /**
     * @brief Get the current time as a string
     * @return The current time as a string
     */
    static std::string getTime();
};


#endif //RICOCHETSOCKETSSERVER_LOGS_H
