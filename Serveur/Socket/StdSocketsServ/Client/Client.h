#ifndef RICOCHETSOCKETSSERVER_CLIENT_H
#define RICOCHETSOCKETSSERVER_CLIENT_H

#include "../socket.h"

class Client {
public:
    Client(SOCKET& socket, SOCKADDR_IN& sockAddr);
    ~Client();

private:
    SOCKET socket;
    SOCKADDR_IN sockAddr;
};


#endif //RICOCHETSOCKETSSERVER_CLIENT_H
