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

#include <thread>
#include <mutex>
#include <csignal>

#include "Serveur.h"
#include "clients/Client.h"
#include "logs/Logs.h"
#include "configue.h"

void signalHandler(int signum) {
    Serveur::end();
    #if defined (WIN32)
        WSACleanup();
    #endif
    Logs::write("Server shutdown",LOG_LEVEL_INFO);
    exit(EXIT_SUCCESS);
}

int main() {
    #if defined (WIN32)
        WSADATA WSAData;
        int _erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
        if(_erreur) return EXIT_FAILURE;
    #endif

    signal(SIGTERM, signalHandler);
    #if DEV_MODE!=0
        signal(SIGINT, signalHandler);
        signal(SIGPIPE, signalHandler);
        signal(SIGABRT, signalHandler);
    #endif

    if(!Logs::write("Start Server",LOG_LEVEL_INFO)) return EXIT_FAILURE;

    if(Serveur::init()) return EXIT_FAILURE;

    Client clients[MAX_CLIENTS];

    std::thread acceptThread(Serveur::acceptLoop);

    acceptThread.join();

    Serveur::end();

    #if defined (WIN32)
        WSACleanup();
    #endif

    Logs::write("Server shutdown",LOG_LEVEL_INFO);

    return 0;
}
