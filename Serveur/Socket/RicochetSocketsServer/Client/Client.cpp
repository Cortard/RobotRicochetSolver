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
    Logs::write("Connection test with client id: "+std::to_string(id)+" result: "+std::to_string(socket->testConnection()),LOG_LEVEL_INFO);
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