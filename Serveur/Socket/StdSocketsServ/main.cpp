#include <csignal>

#include <iostream>

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

    std::cout << "Start Server" << std::endl;
    Server::run();
    std::cout << "Server shutdown" << std::endl;

    #if defined (WIN32)
        WSACleanup();
    #endif

    return 0;
}
