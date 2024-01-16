#ifndef STDSOCKETSSERVER_CONFIGUE_H
#define STDSOCKETSSERVER_CONFIGUE_H


#define DEV_MODE 1

#if DEV_MODE==0

    #define IP "195.201.205.241"
    #define PORT 9090
    #define MAX_CLIENTS 5
    #define LOG_PATH "/home/ricochet/logs.txt"
    #define PICTURE_PATH "/home/ricochet/temp_picture/"

#else

    #define IP "127.0.0.1"
    #define PORT 9090
    #define MAX_CLIENTS 5
    #define LOG_PATH "./logs.txt"
    #define PICTURE_PATH "./picture/"

#endif

#endif //STDSOCKETSSERVER_CONFIGUE_H
