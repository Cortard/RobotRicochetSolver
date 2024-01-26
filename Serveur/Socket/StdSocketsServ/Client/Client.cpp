#include "Client.h"

Client::Client(SOCKET& socket, SOCKADDR_IN& sockAddr) : socket(socket), sockAddr(sockAddr) {
}

Client::~Client() {
    closesocket(socket);
}
