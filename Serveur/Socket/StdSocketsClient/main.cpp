#include <iostream>
#include "configue.h"
#include "sha256/sha256.h"

#include <opencv2/opencv.hpp>

#include "../RicochetSocketsServer/Socket/Socket.h"

int main() {
    //conecte to the server
    if(Socket::init()!=0){
        std::cerr<<"Error initializing the socket system"<<std::endl;
        return -1;
    }

    auto* clientSocket = new Socket(IP, PORT);
    printf("res : %d",clientSocket->testConnection());
    delete clientSocket;

    Socket::end();

    return 0;
}
