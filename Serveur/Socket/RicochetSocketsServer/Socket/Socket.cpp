#include "Socket.h"
#include "../config.h"

bool Socket::isClassInit = false;
int Socket::True = 1;

int Socket::init() {
    #if defined (WIN32)
        WSADATA WSAData;
        int _erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
        if(_erreur) return EXIT_FAILURE;
    #endif
    isClassInit = true;
    return EXIT_SUCCESS;
}

void Socket::end() {
    #if defined (WIN32)
        WSACleanup();
    #endif
}

Socket::Socket(const char *ip, unsigned short port): sock(0), sockAddrIn() {
    if(!isClassInit && Socket::init() == EXIT_FAILURE) throw std::runtime_error("Socket class initialization failed");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) throw std::runtime_error("Socket creation failed");

    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&True,sizeof(int));

    sockAddrIn.sin_addr.s_addr = inet_addr(ip);
    sockAddrIn.sin_family = AF_INET;
    sockAddrIn.sin_port = htons(port);

    socklen_t sockAddrInterSize = sizeof(sockAddrIn);
    if(bind(sock, (SOCKADDR*)&sockAddrIn, sockAddrInterSize) != 0  ) {
        closesocket(sock);
        throw std::runtime_error("Socket binding failed");
    }

    if(listen(sock, MAX_CLIENTS) != 0) {
        closesocket(sock);
        throw std::runtime_error("Socket listening failed");
    }
}

Socket::Socket(SOCKET sock, SOCKADDR_IN addressInternet) : sock(sock), sockAddrIn(addressInternet) {}

Socket::~Socket() {
    closesocket(sock);
}

Socket *Socket::accept() const {
    SOCKET clientSocket;
    SOCKADDR_IN clientAddressInternet;
    socklen_t clientAddrInterSize = sizeof(clientAddressInternet);

    clientSocket = ::accept(sock, (SOCKADDR*)&clientAddressInternet, &clientAddrInterSize);
    if(clientSocket == SOCKET_ERROR) {
        return nullptr;
    }

    return new Socket(clientSocket, clientAddressInternet);
}

size_t Socket::send(const char *buffer, int length) const {
    return ::send(sock, buffer, length, 0);
}

size_t Socket::receive(char *buffer, int length) const {
    return ::recv(sock, buffer, length, 0);
}

std::string Socket::toString() const {
    return std::string(inet_ntoa(sockAddrIn.sin_addr)) + ":" + std::to_string(ntohs(sockAddrIn.sin_port));
}
