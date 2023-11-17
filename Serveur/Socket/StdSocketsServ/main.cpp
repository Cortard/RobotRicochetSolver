#include <iostream>
#include <fstream>
#include <ctime>

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

#define IP "195.201.205.241"//195.201.205.241 127.0.0.1
#define PORT 9090

int openLogs(std::ofstream& file)
{
    file = std::ofstream("/home/ricochet/logs.txt");

    if (file.is_open())
    {
        return 1;
    }
    return 0;
}
void log(std::ofstream& file,const std::string& msg)
{
    time_t now = time(nullptr);
    std::string dt = ctime(&now);
    dt = dt.substr(0, dt.length() - 1);
    file<<dt<<": ";
    file<<msg;
    file<<std::endl;
}
void closeLogs(std::ofstream& file)
{
    file.close();
}

int main() {
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif

    if(erreur) return -1;

    std::ofstream logs;
    if(!openLogs(logs)) return -1;
    log(logs,"ouverture logs");

    SOCKET sockServ;
    sockServ = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sockAddrInter;
    sockAddrInter.sin_addr.s_addr = inet_addr(IP);//htonl(INADDR_ANY)
    sockAddrInter.sin_family = AF_INET;
    sockAddrInter.sin_port = htons(PORT);
    socklen_t sockAddrInterSize = sizeof(sockAddrInter);

    if( bind(sockServ,(SOCKADDR*)&sockAddrInter,sizeof(sockAddrInter)) != 0  ) {
        log(logs,"Bind error");
        return -1;
    }

    log(logs,"Bind Done");
    log(logs,"IP: " + std::string(inet_ntoa(sockAddrInter.sin_addr)));

    if(listen(sockServ, 5) != 0){
        log(logs,"Listen error");
        return -1;
    }
    log(logs,"Listen Done");


    while(true){
        SOCKET clientSock=accept(sockServ, (SOCKADDR*)&sockAddrInter, &sockAddrInterSize);
        if( clientSock == SOCKET_ERROR ) {
            log(logs,"Connect error");
            break;
        }

        log(logs,"Connect done, Client IP: " + std::string(inet_ntoa(sockAddrInter.sin_addr)));

        std::string msg = "Hello world";
        size_t msgSize[] = {msg.size()};
        if(send(clientSock, (char*)msgSize, sizeof(size_t), 0)==SOCKET_ERROR){
            log(logs,"Send size error");
            closesocket(clientSock);
            break;
        }
        log(logs,"Send size");

        if(send(clientSock, msg.c_str(), (int)msgSize[0], 0)==SOCKET_ERROR){
            log(logs,"Send message error");
            closesocket(clientSock);
            break;
        }
        log(logs,"Send message");

        closesocket(clientSock);
        break;
    }

    closesocket(sockServ);

    #if defined (WIN32)
        WSACleanup();
    #endif

    return 0;
}
