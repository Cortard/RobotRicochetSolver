#include "Client.h"

Client::Client() : sock(INVALID_SOCKET), state(STATE_DISCONNECTED)
{
}

Client::Client(SOCKET sock, int id) : sock(sock), state(STATE_CONNECTED)
{
}

SOCKET Client::getSock() const {
    return this->sock;
}

int Client::getState() const {
    return this->state;
}

void Client::setState(int newState) {
    this->state=newState;
}

void Client::close() const {
    closesocket(this->sock);
}

