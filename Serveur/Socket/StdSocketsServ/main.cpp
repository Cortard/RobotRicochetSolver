#include <iostream>
#include "devMode.h"
#include "logs/Logs.h"

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

#if DEV_MODE==1
    #define IP "127.0.0.1"
    #define PORT 9090
#else
    #define IP "195.201.205.241"
    #define PORT 9090
#endif

int main() {
    #if defined (WIN32)
        WSADATA WSAData;
        int _erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
        if(_erreur) return -1;
    #endif


    if(!Logs::write("Start Server",LOG_LEVEL_INFO)) return -1;

    Logs::write("Initialisation  socket",LOG_LEVEL_INFO);
    SOCKET sockServ;
    sockServ = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sockAddrInter;
    sockAddrInter.sin_addr.s_addr = inet_addr(IP);//htonl(INADDR_ANY)
    sockAddrInter.sin_family = AF_INET;
    sockAddrInter.sin_port = htons(PORT);
    socklen_t sockAddrInterSize = sizeof(sockAddrInter);

    if( bind(sockServ,(SOCKADDR*)&sockAddrInter,sizeof(sockAddrInter)) != 0  ) {
        Logs::write("Bind error",LOG_LEVEL_ERROR);
        return -1;
    }

    Logs::write("Bind Done for IP: " + std::string(inet_ntoa(sockAddrInter.sin_addr)) + " PORT : " + std::to_string(htons(sockAddrInter.sin_port)),LOG_LEVEL_DETAILS);

    if(listen(sockServ, 5) != 0){
        Logs::write("Listen error",LOG_LEVEL_ERROR);
        return -1;
    }
    Logs::write("Listen Done",LOG_LEVEL_DETAILS);


    while(true){
        SOCKET clientSock=accept(sockServ, (SOCKADDR*)&sockAddrInter, &sockAddrInterSize);
        if( clientSock == SOCKET_ERROR ) {
            Logs::write("Accept error",LOG_LEVEL_ERROR);
            break;
        }

        Logs::write("Connect done, Client IP: " + std::string(inet_ntoa(sockAddrInter.sin_addr)),LOG_LEVEL_DETAILS);

        std::string msg = "Hello world";
        size_t msgSize[] = {msg.size()};
        if(send(clientSock, (char*)msgSize, sizeof(size_t), 0)==SOCKET_ERROR){
            Logs::write("Send size error",LOG_LEVEL_ERROR);
            closesocket(clientSock);
            break;
        }
        Logs::write("Send size",LOG_LEVEL_DETAILS);

        if(send(clientSock, msg.c_str(), (int)msgSize[0], 0)==SOCKET_ERROR){
            Logs::write("Send message error",LOG_LEVEL_ERROR);
            closesocket(clientSock);
            break;
        }
        Logs::write("Send message",LOG_LEVEL_DETAILS);

        closesocket(clientSock);
        break;
    }

    closesocket(sockServ);
    Logs::write("Close socket",LOG_LEVEL_INFO);

    #if defined (WIN32)
        WSACleanup();
    #endif

    Logs::write("Server shutdown",LOG_LEVEL_INFO);

    return 0;
}
