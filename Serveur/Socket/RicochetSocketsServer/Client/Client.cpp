#include "Client.h"

Client::Client() : busy(false), socket(nullptr), id(0), shouldStop(false) {
}

void Client::startProcess(Socket* newSocket, unsigned int newId) {
    if(processThread.joinable())
        processThread.join();
    processThread = std::thread(&Client::process, this, newSocket, newId);
}

void Client::setUp(Socket* newSocket, unsigned int newId) {
    this->busy = true;
    this->socket = newSocket;
    this->id = newId;
    this->shouldStop = false;
}

void Client::process(Socket* newSocket, unsigned int newId){
    setUp(newSocket, newId);
    processLoop();
    delete socket;
    socket = nullptr;
    this->busy = false;
}

void Client::processLoop(){ //TODO: implement
    /*
    int i=0;
    while (!shouldStop && i<5) {
        sleep(1);
        ++i;
    }
    if(shouldStop) Logs::write("Client process stopped id: "+std::to_string(id),LOG_LEVEL_WARNING);*/
    int size;
    if(socket->receive((char*)&size, sizeof(int))!=sizeof(int)) {
        Logs::write("Error while receiving size",LOG_LEVEL_WARNING);
        return;
    }
    char* buffer = new char[size];
    if(socket->receive(buffer, size)!=size) {
        Logs::write("Error while receiving buffer",LOG_LEVEL_WARNING);
        delete[] buffer;
        return;
    }

    Logs::write("Received: "+std::string(buffer),LOG_LEVEL_INFO);

    if(socket->send(buffer, size)!=size) {
        Logs::write("Error while sending buffer",LOG_LEVEL_WARNING);
    }

    delete[] buffer;

    sleep(5);
}

void Client::askStop() {
    shouldStop = true;
}

void Client::waitStop() {
    processThread.join();
}

bool Client::isBusy() {
    return busy;
}

Client::~Client() {
    delete socket;
}