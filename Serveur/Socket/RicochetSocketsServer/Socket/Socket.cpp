#include <random>
#include "Socket.h"
#include "../config.h"
#include "../sha256/sha256.h"

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

    isServer = true;
}

Socket::Socket(SOCKET sock, SOCKADDR_IN addressInternet, bool isServer): sock(sock), sockAddrIn(addressInternet), isServer(isServer) {}

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

    return new Socket(clientSocket, clientAddressInternet, false);
}

ssize_t Socket::send(const char *buffer, int length) const {
    return ::send(sock, buffer, length, 0);
}

ssize_t Socket::receive(char *buffer, int length) const {
    return receive(buffer, length, false);
}

ssize_t Socket::receive(char* buffer, int length, bool waitAll) const{
    return ::recv(sock, buffer, length, waitAll ? MSG_WAITALL : 0);
}

int Socket::testConnection() const {
    #define sizeBufferTest 8000
    int buffer[sizeBufferTest];
    std::random_device random_device; // create object for seeding
    std::mt19937 engine{random_device()}; // create engine and seed it
    std::uniform_int_distribution dist(0,255); // create distribution for integers with [1; 9] range
    for(int & i : buffer) i = dist(engine);

    size_t bytesSent = send(reinterpret_cast<char*>(buffer), sizeof(buffer));
    if (bytesSent != sizeof(buffer)) {
        return -1;
    }

    size_t size;
    if(receive(reinterpret_cast<char*>(&size), sizeof(size), true)!=sizeof(size)) {
        return -1;
    }

    char* receiveBuffer = new char[size];
    if(receive(receiveBuffer, (int)size)!=size) {
        delete[] receiveBuffer;
        return -1;
    }
    std::string receivedChecksum = std::string(receiveBuffer);
    delete[] receiveBuffer;

    SHA256 sha256;
    auto checkSum = sha256(buffer, sizeof(buffer));

    if(checkSum != receivedChecksum) return 1;
    return 0;
}

std::string Socket::toString() const {
    return std::string(inet_ntoa(sockAddrIn.sin_addr)) + ":" + std::to_string(ntohs(sockAddrIn.sin_port));
}
