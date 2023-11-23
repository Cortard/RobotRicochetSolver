#if defined (WIN32)
#include <winsock2.h>
typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close (s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <iostream>
#include "configue.h"

int main() {
    #if defined (WIN32)
        WSADATA WSAData;
        int _erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
        if(_erreur) return -1;
    #endif

    SOCKET sockServ;
    sockServ = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sockAddrInter;
    sockAddrInter.sin_addr.s_addr = inet_addr(IP);//htonl(INADDR_ANY)
    sockAddrInter.sin_family = AF_INET;
    sockAddrInter.sin_port = htons(PORT);

    if(connect(sockServ, (SOCKADDR*)&sockAddrInter, sizeof (sockAddrInter))== SOCKET_ERROR) {
        printf("Impossible de se connecter\n");
        return EXIT_FAILURE;
    }
    printf("Connecté a %s:%d\n", inet_ntoa(sockAddrInter.sin_addr), htons(sockAddrInter.sin_port));

    char typeDate= 1;
    int result=send(sockServ, (char *)&typeDate, sizeof(typeDate), 0);
    if(result==SOCKET_ERROR) {
        printf("Impossible d'envoyer le type de donnée\n");
        return EXIT_FAILURE;
    }
    printf("Type de donnée envoyé\n");

    char typeDateReceive;
    result=recv(sockServ, &typeDateReceive, sizeof(typeDate),0);
    if(result==SOCKET_ERROR) {
        printf("Impossible de recevoir le type de donnée\n");
        return EXIT_FAILURE;
    }
    printf("Type de donnée reçu\n");

    if(typeDateReceive!=typeDate) {
        printf("Type de donnée reçu différent de celui envoyé\n");
        return EXIT_FAILURE;
    }
    printf("Type de donnée reçu identique à celui envoyé\n");

    Sleep(500);
#if defined (WIN32)
    WSACleanup();
#endif
    return 0;
}
