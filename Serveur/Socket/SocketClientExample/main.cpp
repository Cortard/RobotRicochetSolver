#include <iostream>
#include "config.h"
#include "sha256/sha256.h"

#include <opencv2/opencv.hpp>

#include "../RicochetSocketsServer/Socket/Socket.h"
#include "../RicochetSocketsServer/Socket/Packet/CustomPacket/ConnectionTestRequestPacket.h"

int main() {
    if(Socket::init()!=0){
        std::cerr<<"Error initializing the socket system"<<std::endl;
        return -1;
    }

    auto* clientSocket = new Socket(IP, PORT);

    printf("Sent connection test result : %d\n", clientSocket->testConnection());

    auto* packet= reinterpret_cast<ConnectionTestRequestPacket*>(clientSocket->receive(Packet::Type::CONNECTION_TEST_REQUEST, true));
    if(packet== nullptr){
        printf("Error receiving connection test\n");
        delete clientSocket;
        return -1;
    }printf("Received connection test result : %d\n", packet->getResult());
    delete packet;

    delete clientSocket;

    Socket::end();

    return 0;
}
