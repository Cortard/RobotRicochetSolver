#include "Client.h"

int Client::nextIdSlot=0;

Client::Client() : slotNum(nextIdSlot++), state(STATE_DISCONNECTED), socket(INVALID_SOCKET), output(nullptr)
{
}


void Client::connect(SOCKET client)
{
    state=STATE_NEW_CONNECTED;
    this->socket=client;
    output= nullptr;
}

template void Client::clearOutput<char>();
template void Client::clearOutput<unsigned int>();

template <typename T>
void Client::clearOutput() {
    delete[] static_cast<T*>(output);
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




