#include "Server.h"
#include <cstdlib>
#include <cstring>

bool Server::running = false;
Socket* Server::socket = nullptr;

Client Server::clients[MAX_CLIENTS];
unsigned int Server::nextClientId = 1;

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
    for(auto & client : clients)
        if(client.busy) client.askStop();

    for(auto & client : clients)
        if(client.busy) client.waitStop();

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
        Logs::write("Slot : "+std::to_string(slot), LOG_LEVEL_DEBUG);
        if(slot == -1) {
            Logs::write("No empty slot for new client ("+clientSocket->toString()+")", LOG_LEVEL_WARNING);
            delete clientSocket;
            continue;
        }

        Logs::write("New client ("+clientSocket->toString()+") slot : "+std::to_string(slot)+" id : "+std::to_string(nextClientId), LOG_LEVEL_INFO);
        clients[slot].startProcess(clientSocket, nextClientId++);
    }
}

int Server::foundEmptySlot() {
    for(int i = 0; i < MAX_CLIENTS; i++) {
        if(!clients[i].busy) {
            return i;
        }
    }
    return -1;
}