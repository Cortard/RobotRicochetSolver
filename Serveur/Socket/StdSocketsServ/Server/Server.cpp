#include "Server.h"
#include <cstdlib>

bool Server::running = false;
SOCKET Server::sock;
SOCKADDR_IN Server::addressInternet;

int Server::run() {
    if(init()) return EXIT_FAILURE;
    loop();
    return 0;
}

void Server::stop() {
    running = false;
    closesocket(sock);
}

int Server::init() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) {
        return EXIT_FAILURE;
    }

    addressInternet.sin_addr.s_addr = inet_addr(IP);
    addressInternet.sin_family = AF_INET;
    addressInternet.sin_port = htons(PORT);

    socklen_t sockAddrInterSize = sizeof(addressInternet);
    if( bind(sock,(SOCKADDR*)&addressInternet,sockAddrInterSize) != 0  ) {
        return EXIT_FAILURE;
    }

    if(listen(sock, MAX_CLIENTS) != 0) {
        return EXIT_FAILURE;
    }

    return 0;
}

void Server::loop() {
    running = true;
    while(running) {
        SOCKET clientSocket;
        SOCKADDR_IN clientAddressInternet;
        socklen_t clientAddrInterSize = sizeof(clientAddressInternet);

        clientSocket = accept(sock, (SOCKADDR*)&clientAddressInternet, &clientAddrInterSize);
        if(clientSocket == INVALID_SOCKET) {
            continue;
        }

        //TODO: add client to list
    }
}