#include "Server.h"
#include <cstdlib>
#include <cstring>

bool Server::running = false;
Socket* Server::socket = nullptr;

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
    delete socket;
}

int Server::init() {
    Logs::write("Initializing server", LOG_LEVEL_INFO);

    try {
        socket = new Socket(IP,PORT);
    } catch (std::exception & e) {
        Logs::write("Error while creating socket: "+std::string(e.what()), LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    memset(clients, 0, sizeof(clients));

    return 0;
}

void Server::loop() {
    Logs::write("Server loop started", LOG_LEVEL_INFO);
    running = true;
    while(running) {
        Socket* clientSocket = socket->accept();

        if(clientSocket == nullptr) {
            if(running) Logs::write("Error while accepting client", LOG_LEVEL_WARNING);
            continue;
        }

        int slot = foundEmptySlot();
        if(slot == -1) {
            Logs::write("No empty slot for new client ("+clientSocket->toString()+")", LOG_LEVEL_WARNING);
            delete clientSocket;
            continue;
        }

        Logs::write("New client ("+clientSocket->toString()+")", LOG_LEVEL_DETAILS);
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