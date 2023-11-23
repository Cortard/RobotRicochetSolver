#include "Serveur.h"

SOCKET Serveur::sock;
SOCKADDR_IN Serveur::addressInternet;
Client Serveur::slots[MAX_CLIENTS];

int Serveur::init() {
    Logs::write("Initialisation socket",LOG_LEVEL_INFO);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) {
        Logs::write("Socket error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Socket Done",LOG_LEVEL_DETAILS);

    addressInternet.sin_addr.s_addr = inet_addr(IP);//htonl(INADDR_ANY)
    addressInternet.sin_family = AF_INET;
    addressInternet.sin_port = htons(PORT);
    socklen_t sockAddrInterSize = sizeof(addressInternet);

    if( bind(sock,(SOCKADDR*)&addressInternet,sockAddrInterSize) != 0  ) {
        Logs::write("Bind error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Bind Done for IP: " + std::string(inet_ntoa(addressInternet.sin_addr)) + " PORT : " + std::to_string(htons(addressInternet.sin_port)),LOG_LEVEL_DETAILS);

    if(listen(sock, 5) != 0){
        Logs::write("Listen error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Listen Done",LOG_LEVEL_DETAILS);

    for(Client & slot: slots) slot.state=STATE_DISCONNECTED;

    return 0;
}

void Serveur::close() {
    shutdown(sock, 2);
    closesocket(sock);
    Logs::write("Close socket",LOG_LEVEL_INFO);
}

#include <iostream>
int Serveur::foundEmptySlot()
{
    int i=0;
    std::unique_lock<std::mutex> lock(slots[i].mutex);
    while(slots[i].state!=STATE_DISCONNECTED){
        lock.unlock();
        ++i;
        if(i<MAX_CLIENTS)  lock = std::unique_lock<std::mutex>(slots[i].mutex);
        else break;
    }
    return i;
}

#include <iostream>
void Serveur::acceptLoop() {
    Logs::write("Accept loop start",LOG_LEVEL_INFO);

    SOCKADDR_IN sockAddrClient;
    socklen_t sockAddrClientSize=sizeof(SOCKADDR_IN);

    while(true){
        SOCKET newClientSock=accept(sock, (SOCKADDR*)&sockAddrClient, &sockAddrClientSize);
        if( newClientSock == SOCKET_ERROR ) {
            continue;
        }
        Logs::write("Client accepted IP" + std::string(inet_ntoa(sockAddrClient.sin_addr)) + " PORT : " + std::to_string(htons(sockAddrClient.sin_port)),LOG_LEVEL_DETAILS);

        int freeSlot=foundEmptySlot();
        if(freeSlot==MAX_CLIENTS){
            Logs::write("Max client reached",LOG_LEVEL_WARNING);
            continue;
        }
        std::unique_lock<std::mutex> lock(slots[freeSlot].mutex);
        slots[freeSlot].connect(newClientSock);
        Logs::write("Client added on slot " + std::to_string(freeSlot),LOG_LEVEL_VERBOSE);
    }
}

void Serveur::getTypeDataClient(Client* slot){
    slot->output=new char[1];
    int result = recv(slot->socket, (char*)slot->output, sizeof(char), MSG_WAITALL);
    switch (result) {
        case SOCKET_ERROR:
            Logs::write("Error recv", LOG_LEVEL_ERROR);
            delete (char*)slot->output;
            slot->output= nullptr;
            slot->disconnect();
            return;
        case 0:
            Logs::write("Client disconnected", LOG_LEVEL_VERBOSE);
            delete (char*)slot->output;
            slot->output= nullptr;
            slot->disconnect();
            return;
    }

    std::unique_lock<std::mutex> lock(slot->mutex);
    slot->state=STATE_RECEIVED_TYPE_DATE;
    lock.unlock();
}

void Serveur::confirmTypeDataClient(Client *slot) {
    int result = send(slot->socket, (char*)slot->output, sizeof(char), 0);
    switch (result) {
        case SOCKET_ERROR:
            Logs::write("Error send", LOG_LEVEL_ERROR);
            delete (char*)slot->output;
            slot->output= nullptr;
            slot->disconnect();
            return;
        case 0:
            Logs::write("Client disconnected", LOG_LEVEL_VERBOSE);
            delete (char*)slot->output;
            slot->output= nullptr;
            slot->disconnect();
            return;
    }
    std::unique_lock<std::mutex> lock(slot->mutex);
    slot->state=STATE_SENT_TYPE_DATA_CONFIRMATION;
    lock.unlock();
}

void Serveur::processLoop(){
    Logs::write("Process loop start",LOG_LEVEL_INFO);
    while (true) {
        for (int i=0;i<MAX_CLIENTS; ++i) {
            Client& slot = slots[i];
            std::unique_lock<std::mutex> lock(slot.mutex);
            int state = slot.state;
            lock.unlock();
            if(state%2) continue;// if state is odd, the slot is processing or disconnected
            switch (state) {
                case STATE_DISCONNECTED:
                    break;
                case STATE_NEW_CONNECTED:
                    Logs::write("Receiving type from client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    slot.state = STATE_RECEIVING_TYPE_DATA;
                    std::thread(Serveur::getTypeDataClient, &slot).detach();
                    break;
                case STATE_RECEIVED_TYPE_DATE:
                    Logs::write("Sending typeConfirm to client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    slot.state = STATE_SENDING_TYPE_DATA_CONFIRMATION;
                    std::thread(Serveur::confirmTypeDataClient, &slot).detach();
                    break;
                case STATE_SENT_TYPE_DATA_CONFIRMATION:
                    Logs::write("Client process on slot " + std::to_string(i) + " is done",LOG_LEVEL_VERBOSE);
                    shutdown(slot.socket, 2);
                    std::unique_lock<std::mutex> lockEnd(slot.mutex);
                    delete (char *)slot.output;
                    slot.output= nullptr;
                    slot.disconnect();
                    lockEnd.unlock();
                    break;
            }
        }
    }
}