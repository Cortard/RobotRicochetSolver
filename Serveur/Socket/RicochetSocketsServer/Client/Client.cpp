#include "Client.h"
#include "../Socket/Packet/CustomPacket/ConnectionTestRequestPacket.h"

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
    Logs::write("Client id : "+std::to_string(id)+" process started",LOG_LEVEL_DETAILS);
    auto* packet = reinterpret_cast<ConnectionTestRequestPacket*>(socket->receive(Packet::Type::CONNECTION_TEST_REQUEST, true));
    if(packet == nullptr) {
        Logs::write("Client id : "+std::to_string(id)+" process stopped",LOG_LEVEL_WARNING);
        return;
    }
    Logs::write("Client id : "+std::to_string(id)+" received connection test result : "+std::to_string(packet->getResult()),LOG_LEVEL_VERBOSE);
    delete packet;
    Logs::write("Client id : "+std::to_string(id)+" sent connection test result : "+std::to_string(socket->testConnection()),LOG_LEVEL_VERBOSE);
    Logs::write("Client id : "+std::to_string(id)+" process ended",LOG_LEVEL_DETAILS);
}

void Client::askStop() {
    shouldStop = true;
}

void Client::waitStop() {
    processThread.join();
}

bool Client::isBusy() const {
    return busy;
}

Client::~Client() {
    delete socket;
}