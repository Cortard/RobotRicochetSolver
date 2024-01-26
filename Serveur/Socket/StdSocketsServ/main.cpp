#include <csignal>

#include <iostream>

#include "Logs/Logs.h"
#include "Server/Server.h"

void stopServer(int signum) {
    Server::stop();
}

int main() {
    #if defined (WIN32)
        WSADATA WSAData;
        int _erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
        if(_erreur) return EXIT_FAILURE;
    #endif

    signal(SIGTERM, stopServer);
    signal(SIGINT, stopServer);
    signal(SIGPIPE, stopServer);
    signal(SIGABRT, stopServer);

    if(!Logs::write("Start Server",LOG_LEVEL_INFO)) return EXIT_FAILURE;
    Server::run();

    #if defined (WIN32)
        WSACleanup();
    #endif

    return 0;
}
