#ifndef STDSOCKETSSERVER_CONFIGUE_H
#define STDSOCKETSSERVER_CONFIGUE_H


#define DEV_MODE 0

#if DEV_MODE==0

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

#endif //STDSOCKETSSERVER_CONFIGUE_H
