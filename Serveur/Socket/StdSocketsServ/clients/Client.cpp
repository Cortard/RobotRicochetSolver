#include "Client.h"
#include "../solver/Game.h"

int Client::nextIdSlot=0;

Client::Client() : slotNum(nextIdSlot++), state(STATE_DISCONNECTED), socket(INVALID_SOCKET), output(nullptr)
{
}


void Client::connect(SOCKET client)
{
    this->socket=client;
    output= nullptr;
    state=STATE_NEW_CONNECTED;
}

template void Client::clearOutput<char>();
template void Client::clearOutput<Game>();
template void Client::clearOutput<unsigned int>();
template void Client::clearOutput<unsigned char>();
template <typename T>
void Client::clearOutput() {
    if (output != nullptr) {
        if (std::is_array<T>::value) {
            delete[] static_cast<T*>(output);
        } else {
            delete static_cast<T*>(output);
        }
        output = nullptr;
    }
}

void Client::disconnect()
{
    if(output!= nullptr) throw std::logic_error("Client output should be null to disconnect client");
    shutdown(socket,2);
    closesocket(socket);
    this->socket=INVALID_SOCKET;
    state=STATE_DISCONNECTED;
}

Client::~Client()  {
    if(state!=STATE_DISCONNECTED)
        closesocket(socket);
}




