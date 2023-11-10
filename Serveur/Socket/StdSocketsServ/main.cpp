#include <iostream>

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

#define IP "127.0.0.1"
#define PORT 49152

int main() {
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif

    if(erreur) return -1;

    SOCKET sockServ;
    sockServ = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sockAddrInter;
    sockAddrInter.sin_addr.s_addr = inet_addr(IP);//htonl(INADDR_ANY)
    sockAddrInter.sin_family = AF_INET;
    sockAddrInter.sin_port = htons(PORT);
    socklen_t sockAddrInterSize = sizeof(sockAddrInter);

    if( bind(sockServ,(SOCKADDR*)&sockAddrInter,sizeof(sockAddrInter)) != 0  ) {
        std::cout << "Bind error" << std::endl;
        return -1;
    }
    std::cout << "Bind Done" << std::endl;
    std::cout << "IP: " << inet_ntoa(sockAddrInter.sin_addr) << std::endl;
    std::cout << "Port: " << htons(sockAddrInter.sin_port) << std::endl;

    if(listen(sockServ, 5) != 0){
        std::cout << "Listen error" << std::endl;
        return -1;
    }
    std::cout << "Listen Done" << std::endl;


    while(true){
        SOCKET clientSock=accept(sockServ, (SOCKADDR*)&sockAddrInter, &sockAddrInterSize);
        if( clientSock == SOCKET_ERROR ) {
            std::cout << "Connect error" << std::endl;
            break;
        }

        std::cout << "Connect done" << std::endl;
        std::cout << "Client IP: " << inet_ntoa(sockAddrInter.sin_addr) << std::endl;
        
        std::string msg = "Hello world";
        size_t msgSize[] = {msg.size()};
        if(send(clientSock, (char*)msgSize, sizeof(size_t), 0)==SOCKET_ERROR){
            std::cout << "Send size error" << std::endl;
            closesocket(clientSock);
            break;
        }
        std::cout << "Send size" << std::endl;

        if(send(clientSock, msg.c_str(), (int)msgSize[0], 0)==SOCKET_ERROR){
            std::cout << "Send message error" << std::endl;
            closesocket(clientSock);
            break;
        }
        std::cout << "Send message" << std::endl;

        closesocket(clientSock);
        break;
    }

    closesocket(sockServ);

    #if defined (WIN32)
        WSACleanup();
    #endif

    return 0;
}
