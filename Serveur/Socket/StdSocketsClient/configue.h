#ifndef STDSOCKETSCLIENT_CONFIGUE_H
#define STDSOCKETSCLIENT_CONFIGUE_H

#define DEV_MODE 1

#if DEV_MODE==0
    #define IP "195.201.205.241"
    #define PORT 9090
#else
    #define IP "127.0.0.1"
    #define PORT 9090
#endif

#endif //STDSOCKETSCLIENT_CONFIGUE_H
