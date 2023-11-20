#include <thread>
#include "clients/Client.h"
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
    #define MAX_CLIENTS 5
#else
    #define IP "195.201.205.241"
    #define PORT 9090
    #define MAX_CLIENTS 5
#endif

void acceptLoop(SOCKET sockServ, Client clients[MAX_CLIENTS]){
    Logs::write("Accept loop start",LOG_LEVEL_INFO);

    SOCKET* client;
    SOCKADDR* sockAddrClient;
    socklen_t sockAddrClientSize=sizeof(sockAddrClient);
    int nbClient=0;
    while(true){
        SOCKET newClientSock=accept(sockServ, sockAddrClient, &sockAddrClientSize);
        if( newClientSock == SOCKET_ERROR ) {
            continue;
        }
        Logs::write("Accept client IP :" + std::string(inet_ntoa(((SOCKADDR_IN*)sockAddrClient)->sin_addr)) + " PORT : " + std::to_string(htons(((SOCKADDR_IN*)sockAddrClient)->sin_port)),LOG_LEVEL_DETAILS);

        int i=0;
        while(i<MAX_CLIENTS && clients[i].getState()!=STATE_DISCONNECTED) i++;
        if(i==MAX_CLIENTS){
            Logs::write("Max client reached",LOG_LEVEL_WARNING);
            continue;
        }
        clients[i]=Client(newClientSock,i);
        Logs::write("Client added on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
    }
}


#include <unistd.h>
void traitementLoop(Client clients[MAX_CLIENTS]){
    Logs::write("Traitement loop start",LOG_LEVEL_INFO);
    while (true) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].getState() == STATE_CONNECTED) {
                char buffer[1024];
                int size = recv(clients[i].getSock(), buffer, 1024, 0);
                if (size == SOCKET_ERROR) {
                    Logs::write("Error recv", LOG_LEVEL_ERROR);
                    clients[i].close();
                    clients[i].setState(STATE_DISCONNECTED);
                    continue;
                }
                if (size == 0) {
                    Logs::write("Client disconnected", LOG_LEVEL_INFO);
                    clients[i].close();
                    clients[i].setState(STATE_DISCONNECTED);
                    continue;
                }
                buffer[size] = '\0';
                Logs::write("Message received : " + std::string(buffer), LOG_LEVEL_INFO);
                if (send(clients[i].getSock(), buffer, size, 0) == SOCKET_ERROR) {
                    Logs::write("Error send", LOG_LEVEL_ERROR);
                    clients[i].close();
                    clients[i].setState(STATE_DISCONNECTED);
                    continue;
                }
            }
        }
    }
}

int main() {
    #if defined (WIN32)
        WSADATA WSAData;
        int _erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
        if(_erreur) return -1;
    #endif


    if(!Logs::write("Start Server",LOG_LEVEL_INFO)) return -1;

    Logs::write("Initialisation socket",LOG_LEVEL_INFO);
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

    Client clients[MAX_CLIENTS];

    std::thread acceptThread(acceptLoop,sockServ,clients);
    std::thread traitementThread(traitementLoop,clients);

    acceptThread.join();
    traitementThread.join();

    closesocket(sockServ);
    Logs::write("Close socket",LOG_LEVEL_INFO);

    #if defined (WIN32)
        WSACleanup();
    #endif

    Logs::write("Server shutdown",LOG_LEVEL_INFO);

    return 0;
}
