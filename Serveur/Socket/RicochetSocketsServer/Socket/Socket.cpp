#include <random>
#include "Socket.h"
#include "../config.h"
#include "../sha256/sha256.h"
#include "../Logs/Logs.h"

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

Socket::Socket(const char *ip, unsigned short port, bool isServer): sock(0), sockAddrIn(), isServer(isServer) {
    if (!isClassInit && Socket::init() == EXIT_FAILURE)
        throw std::runtime_error("Socket class initialization failed");

    if(isServer) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) throw std::runtime_error("Socket creation failed");

        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &True, sizeof(int));

        sockAddrIn.sin_addr.s_addr = inet_addr(ip);
        sockAddrIn.sin_family = AF_INET;
        sockAddrIn.sin_port = htons(port);

        socklen_t sockAddrInterSize = sizeof(sockAddrIn);
        if (bind(sock, (SOCKADDR *) &sockAddrIn, sockAddrInterSize) != 0) {
            closesocket(sock);
            Logs::write("Socket binding failed", LOG_LEVEL_ERROR);
            throw std::runtime_error("Socket binding failed");
        }

        if (listen(sock, MAX_CLIENTS) != 0) {
            closesocket(sock);
            Logs::write("Socket listening failed", LOG_LEVEL_ERROR);
            throw std::runtime_error("Socket listening failed");
        }

    } else {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) throw std::runtime_error("Socket creation failed");

        sockAddrIn.sin_addr.s_addr = inet_addr(ip);
        sockAddrIn.sin_family = AF_INET;
        sockAddrIn.sin_port = htons(port);

        if (connect(sock, (SOCKADDR *) &sockAddrIn, sizeof(sockAddrIn)) != 0) {
            closesocket(sock);
            throw std::runtime_error("Socket connection failed");
        }
    }
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

ssize_t Socket::send(const char *buffer, size_t size) const {
    if(sendHeader(HeaderFlag::RAW_DATA, size) != sizeof(HeaderFlag) + sizeof(size)) return -1;
    return ::send(sock, buffer, size, 0);
}

ssize_t Socket::receive(char* buffer, bool waitAll) const{
    HeaderFlag flag;
    ssize_t bytesReceived = receiveHeaderFlag(flag);
    if(bytesReceived != sizeof(flag)) return -1;
    switch (flag) {
        case HeaderFlag::HEADER_ONLY:
            return 1;
        case HeaderFlag::RAW_DATA: {
            size_t length;
            bytesReceived = ::recv(sock, reinterpret_cast<char *>(&length), sizeof(length), waitAll?MSG_WAITALL:0);
            if (bytesReceived != sizeof(length)) return bytesReceived;
            return ::recv(sock, buffer, length, waitAll?MSG_WAITALL:0);
        }
        case HeaderFlag::CONNECTION_TEST:
            return testConnection(true);
        default:
            return -1;
    }
}

int Socket::testConnection(bool proposed) const {
    if(proposed) {
        if(receiveConnectionTest() == -1) return -1;
        int result = sendConnectionTest();
        return result;
    } else {
        if(sendHeader(HeaderFlag::CONNECTION_TEST) != sizeof(HeaderFlag)) return -1;
        int result = sendConnectionTest();
        if(result == -1) return -1;
        if(receiveConnectionTest() == -1) return -1;
        return result;
    }
}

std::string Socket::toString() const {
    return std::string(inet_ntoa(sockAddrIn.sin_addr)) + ":" + std::to_string(ntohs(sockAddrIn.sin_port));
}

ssize_t Socket::sendHeader(Socket::HeaderFlag flag) const {
    return ::send(sock, reinterpret_cast<const char*>(&flag), sizeof(flag), 0);
}

ssize_t Socket::sendHeader(Socket::HeaderFlag flag, size_t size) const {
    ssize_t bytesSent = sendHeader(flag);
    if(bytesSent != sizeof(flag)) return bytesSent;
    return bytesSent + ::send(sock, reinterpret_cast<const char*>(&size), sizeof(size), 0);
}

ssize_t Socket::receiveHeaderFlag(Socket::HeaderFlag &flag) const {
    return ::recv(sock, reinterpret_cast<char*>(&flag), sizeof(flag), MSG_WAITALL);
}

ssize_t Socket::receiveDataSize(size_t &size) const {
    return ::recv(sock, reinterpret_cast<char*>(&size), sizeof(size), MSG_WAITALL);
}

ssize_t Socket::receiveData(char *buffer, size_t size, bool waitAll) const {
    return ::recv(sock, buffer, size, waitAll?MSG_WAITALL:0);
}

int Socket::sendConnectionTest() const {
    //size_t size = 1024*1024;
    size_t size = 1024;
    char buffer[size];
    std::random_device random_device; // create object for seeding
    std::mt19937 engine{random_device()}; // create engine and seed it
    std::uniform_int_distribution<unsigned char> dist(0,255); // create distribution for integers with [1, 100000] range
    for(char& i : buffer) i = static_cast<char>(dist(engine));

    if(send(buffer, size) == SOCKET_ERROR) return -1;

    SHA256 sha256;
    auto checkSum = sha256(buffer, sizeof(buffer));

    HeaderFlag flag;
    if(receiveHeaderFlag(flag) != sizeof(flag)) return -1;
    if(flag != HeaderFlag::RAW_DATA) return -1;

    size_t responseSize;
    if(receiveDataSize(responseSize) != sizeof(responseSize)) return -1;
    if(responseSize != checkSum.size()) return -1;

    char response[responseSize];
    if(receiveData(response, responseSize, true) != responseSize) return -1;

    if(checkSum != std::string(response, responseSize)) return 1;
    return 2;
}

int Socket::receiveConnectionTest() const {
    HeaderFlag flag;
    if(receiveHeaderFlag(flag) != sizeof(flag)) return -1;
    if(flag != HeaderFlag::RAW_DATA) return -1;

    size_t size;
    if(receiveDataSize(size) != sizeof(size)) return -1;

    char buffer[size];
    if(receiveData(buffer, size) != size) return -1;

    SHA256 sha256;
    auto checkSum = sha256(buffer, sizeof(buffer));

    if(send(checkSum.c_str(), checkSum.size()) == SOCKET_ERROR) return -1;

    return 2;
}