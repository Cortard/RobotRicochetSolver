#include "Socket.h"
#include "../configue.h"

bool Socket::isClassInit = false;
int Socket::init() {
    #if defined (WIN32)
        WSADATA WSAData;
        int _erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
        if(_erreur) return EXIT_FAILURE;
    #endif
    isClassInit = true;
    return EXIT_SUCCESS;
}

void Socket::clear() {
    #if defined (WIN32)
        WSACleanup();
    #endif
}

Socket::Socket(const char *ip, unsigned short port) {
    if(!isClassInit) throw std::runtime_error("Socket class not initialized");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) throw std::runtime_error("Socket creation failed");

    addressInternet.sin_addr.s_addr = inet_addr(ip);//htonl(INADDR_ANY)
    addressInternet.sin_family = AF_INET;
    addressInternet.sin_port = htons(port);

    socklen_t sockAddrInterSize = sizeof(addressInternet);
    if( bind(sock,(SOCKADDR*)&addressInternet,sockAddrInterSize) != 0  ) {
        closesocket(sock);
        throw std::runtime_error("Socket binding failed");
    }

    if(listen(sock, MAX_CLIENTS) != 0) {
        closesocket(sock);
        throw std::runtime_error("Socket listening failed");
    }
}

Socket::Socket(SOCKET sock, SOCKADDR_IN addressInternet) : sock(sock), addressInternet(addressInternet) {}

Socket::~Socket() {
    closesocket(sock);
}

Socket *Socket::accept() {
    SOCKET clientSocket;
    SOCKADDR_IN clientAddressInternet;
    socklen_t clientAddrInterSize = sizeof(clientAddressInternet);

    clientSocket = ::accept(sock, (SOCKADDR*)&clientAddressInternet, &clientAddrInterSize);
    if(clientSocket == INVALID_SOCKET) {
        return nullptr;
    }

    return new Socket(clientSocket, clientAddressInternet);
}

std::string Socket::toString() const {
    return std::string(inet_ntoa(addressInternet.sin_addr)) + ":" + std::to_string(ntohs(addressInternet.sin_port));
}

SOCKET Socket::getSock() const {
    return sock;
}

SOCKADDR_IN Socket::getAddressInternet() const {
    return addressInternet;
}
