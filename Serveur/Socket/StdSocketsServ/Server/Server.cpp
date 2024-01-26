#include "Server.h"
#include <cstdlib>
#include <cstring>

bool Server::running = false;
SOCKET Server::sock;
SOCKADDR_IN Server::addressInternet;

Client* Server::clients[MAX_CLIENTS];
unsigned int Server::nextClientId = 0;

int Server::run() {
    if(init()) {
        Logs::write("Error while initializing server", LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }Logs::write("Server initialized", LOG_LEVEL_INFO);

    loop();

    return 0;
}

void Server::stop() {
    Logs::write("Stopping server", LOG_LEVEL_INFO);
    for(auto & client : clients) {
        if(client != nullptr) {
            client->askStop();
        }
    }
    for(auto & client : clients) {
        if(client != nullptr) {
            client->waitStop();
            delete client;
        }
    }
    running = false;
    closesocket(sock);
}

int Server::init() {
    Logs::write("Initializing server", LOG_LEVEL_INFO);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) {
        return EXIT_FAILURE;
    }

    addressInternet.sin_addr.s_addr = inet_addr(IP);
    addressInternet.sin_family = AF_INET;
    addressInternet.sin_port = htons(PORT);

    socklen_t sockAddrInterSize = sizeof(addressInternet);
    if( bind(sock,(SOCKADDR*)&addressInternet,sockAddrInterSize) != 0  ) {
        Logs::write("Error while binding socket", LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }Logs::write("Socket bound", LOG_LEVEL_DETAILS);

    if(listen(sock, MAX_CLIENTS) != 0) {
        Logs::write("Error while listening socket", LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }Logs::write("Socket listening", LOG_LEVEL_DETAILS);

    memset(clients, 0, sizeof(clients));

    return 0;
}

void Server::loop() {
    Logs::write("Server loop started", LOG_LEVEL_INFO);
    running = true;
    while(running) {
        SOCKET clientSocket;
        SOCKADDR_IN clientAddressInternet;
        socklen_t clientAddrInterSize = sizeof(clientAddressInternet);

        clientSocket = accept(sock, (SOCKADDR*)&clientAddressInternet, &clientAddrInterSize);
        if(clientSocket == INVALID_SOCKET) {
            if(running) Logs::write("Error while accepting client", LOG_LEVEL_WARNING);
            continue;
        }

        int slot = foundEmptySlot();
        if(slot == -1) {
            Logs::write("No empty slot for new client (IP: "+std::string(inet_ntoa(clientAddressInternet.sin_addr)) + " PORT: " + std::to_string(ntohs(clientAddressInternet.sin_port))+")", LOG_LEVEL_WARNING);
            closesocket(clientSocket);
            continue;
        }

        Logs::write("New client (IP: "+std::string(inet_ntoa(clientAddressInternet.sin_addr)) + " PORT: " + std::to_string(ntohs(clientAddressInternet.sin_port))+") added with id: "+std::to_string(nextClientId), LOG_LEVEL_DETAILS);
        clients[slot] = new Client(clientSocket, nextClientId++);
        clients[slot]->startProcess();
    }
}

int Server::foundEmptySlot() {
    for(int i = 0; i < MAX_CLIENTS; i++) {
        if(clients[i] == nullptr) {
            return i;
        }
    }
    return -1;
}