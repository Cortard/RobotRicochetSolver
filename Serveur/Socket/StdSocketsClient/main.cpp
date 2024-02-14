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
#include "sha256/sha256.h"

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

    #define sizeBufferTest 8000000
    int buffer[sizeBufferTest];
    size_t bytesReceived = recv(sockServ, reinterpret_cast<char*>(buffer), sizeof(buffer), MSG_WAITALL);
    if (bytesReceived == SOCKET_ERROR) {
        printf("Erreur de reception\n");
        // Handle error
        return EXIT_FAILURE;
    } else if (bytesReceived != sizeof(buffer)) {
        printf("Received incomplete data\n");
        // Handle incomplete data
    } else {
        printf("Received buffer successfully\n");
        // Process the received buffer
    }

    SHA256 sha256;
    auto checkSum = sha256(buffer, sizeof(buffer));

    auto size=checkSum.size();
    if(send(sockServ, (char*)&size, sizeof(size), 0) == SOCKET_ERROR) {
        printf("Erreur d'envoi taille\n");
        return EXIT_FAILURE;
    }

    if(send(sockServ, checkSum.c_str(), checkSum.size(), 0) == SOCKET_ERROR) {
        printf("Erreur d'envoi check summ\n");
        return EXIT_FAILURE;
    }

    printf("CheckSum envoye : %s\n", checkSum.c_str());

    sleep(1);

    closesocket(sockServ);

    #if defined (WIN32)
        WSACleanup();
    #endif
    return 0;
}
