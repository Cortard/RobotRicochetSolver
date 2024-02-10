#include "Client.h"

Client::Client(Socket* socket, unsigned int id) : socket(socket), id(id), shouldStop(false) {
}

void Client::startProcess() {
    processThread = std::thread(&Client::processLoop, this);
}

void Client::askStop() {
    shouldStop = true;
}

void Client::waitStop() {
    processThread.join();
}

Client::~Client() {
    delete socket;
}
