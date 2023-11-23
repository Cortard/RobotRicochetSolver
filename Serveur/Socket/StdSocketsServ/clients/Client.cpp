#include "Client.h"

Client::Client() : state(STATE_DISCONNECTED), socket(INVALID_SOCKET), output(nullptr)
{
}

void Client::connect(SOCKET socket)
{
    state=STATE_NEW_CONNECTED;
    this->socket=socket;
    output= nullptr;
}

void Client::disconnect()
{
    if(output!= nullptr) throw std::logic_error("Client output should be null to disconnect client");
    state=STATE_DISCONNECTED;
    closesocket(socket);
    this->socket=INVALID_SOCKET;
}

Client::~Client()  {
    std::unique_lock<std::mutex> lock(mutex);
    closesocket(socket);
}



