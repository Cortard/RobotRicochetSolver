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

#include <opencv2/opencv.hpp>


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
    printf("Connecte a %s:%d\n", inet_ntoa(sockAddrInter.sin_addr), htons(sockAddrInter.sin_port));

    std::string reallyBigString = "Hello World! I am a really big string and I am going to be sent over the network because I am a client and I am going to send this string to the server. I hope the server is ready to receive me!";
    int reallyBigStringSize = reallyBigString.size();
    if (send(sockServ, (char*)&reallyBigStringSize, sizeof(int), 0) == SOCKET_ERROR) {
        printf("Error while sending\n");
        return EXIT_FAILURE;
    }printf("Size sent\n");

    if(send(sockServ, reallyBigString.c_str(), reallyBigString.size(), 0) == SOCKET_ERROR) {
        printf("Error while sending\n");
        return EXIT_FAILURE;
    }printf("String sent\n");

    sleep(10);

    char buffer[reallyBigString.size()];
    if(recv(sockServ, buffer, reallyBigString.size(), 0) == SOCKET_ERROR) {
        printf("Error while receiving\n");
        return EXIT_FAILURE;
    }printf("Received: %s\n", std::string(buffer).c_str());

    closesocket(sockServ);

    #if defined (WIN32)
        WSACleanup();
    #endif
    return 0;
}
