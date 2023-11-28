#ifndef STDSOCKETSSERVER_CONFIGUE_H
#define STDSOCKETSSERVER_CONFIGUE_H


#define DEV_MODE 1

#if DEV_MODE==1

    #define IP "195.201.205.241"
    #define PORT 9090
    #define MAX_CLIENTS 5
    #define LOG_PATH "/home/ricochet/logs.txt"

#else

    #define IP "127.0.0.1"
    #define PORT 9090
    #define MAX_CLIENTS 5
    #define LOG_PATH "./logs.txt"

#endif

#endif //STDSOCKETSSERVER_CONFIGUE_H
