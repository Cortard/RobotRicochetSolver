#ifndef RICOCHETSOCKETSSERVER_CONFIG_H
#define RICOCHETSOCKETSSERVER_CONFIG_H

/**
 * @brief Define is the debug mode is activated, if it's not, the debug output will be disabled
 */
#define DEBUG_OUTPUT 1
/**
 * @brief Define if the log should be printed in the console
 */
#define LOG_IN_CONSOLE 1
/**
 * @brief Define if the log should be printed in a file
 */
#define LOG_IN_FILE 1
/**
 * @brief Define if the socket should be created in localhost
 */
#define LOCAL 0

/**
 * @brief Define all server configuration
 * @note IP and PORT are used to create the socket of the server on
 * @note MAX_CLIENTS is the maximum number of clients that can connect to the server
 * @note LOG_PATH is the path to the log file
 * @note PICTURE_PATH is the path to the picture folder
 * @note BOARD_PATH is the path to the board parts folder
 */
#if LOCAL!=1

    #define IP "195.201.205.241"
    #define PORT 9090
    #define MAX_CLIENTS 5
    #define LOG_PATH "/home/ricochet/logs.txt"
    #define PICTURE_PATH "/home/ricochet/temp_picture/"
    #define BOARD_PATH "/home/ricochet/RobotRicochetSolver/Serveur/Socket/StdSocketsServ/Board_part/"

#else

    #define IP "127.0.0.1"
    #define PORT 9090
    #define MAX_CLIENTS 5
    #define LOG_PATH "./logs.txt"
    #define PICTURE_PATH "./picture/"
    #define BOARD_PATH "../Board_part/"

#endif

#endif //RICOCHETSOCKETSSERVER_CONFIG_H
