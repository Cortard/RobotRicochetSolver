#include <random>
#include "Socket.h"
#include "../config.h"
#include "../sha256/sha256.h"
#include "../Logs/Logs.h"
#include "Packet/PacketDeserializer.h"
#include "Packet/CustomPacket/ConnectionTestRequestPacket.h"

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

ssize_t Socket::send(const Packet &packet) const {
    char* serializedHeader = packet.serializeHeader();
    ssize_t res = ::send(sock, serializedHeader, packet.getSerializationHeaderSize(), 0);
    delete[] serializedHeader;
    if(res != packet.getSerializationHeaderSize()) return -1;

    if(packet.getDataSize() == 0) return res;

    res = ::send(sock, packet.getData(), packet.getDataSize(), 0);
    if(res == SOCKET_ERROR) return -1;
    return res + packet.getSerializationHeaderSize();
}

Packet* Socket::receive(bool acceptConnectionTest) const {
    size_t size;
    ssize_t received = ::recv(sock, reinterpret_cast<char*>(&size), sizeof(size), MSG_WAITALL);
    Logs::write("Received size : " + std::to_string(size), LOG_LEVEL_DEBUG);
    if(received == 0 || received == SOCKET_ERROR) return nullptr;

    char* serializedPacket = new char[size];
    *reinterpret_cast<size_t*>(serializedPacket) = size;
    received = ::recv(sock, serializedPacket+sizeof(size_t), size-sizeof(size_t), MSG_WAITALL);
    if(received == 0 || received == SOCKET_ERROR) {
        delete[] serializedPacket;
        return nullptr;
    }

    Packet* packet = PacketDeserializer::deserialize(serializedPacket);
    delete[] serializedPacket;

    if(acceptConnectionTest && packet && packet->getType() == Packet::Type::CONNECTION_TEST_REQUEST) {
        ((ConnectionTestRequestPacket*)packet)->setResult(testConnection(true));
        if(((ConnectionTestRequestPacket*)packet)->getResult() == -1) {
            delete packet;
            return nullptr;
        }
    }

    return packet;
}

Packet* Socket::receive(Packet::Type type, bool acceptConnectionTest) const {
    Packet* packet = receive(acceptConnectionTest);
    if(packet == nullptr) return nullptr;
    if(acceptConnectionTest && packet->getType() == Packet::Type::CONNECTION_TEST_REQUEST) {
        return packet;
    }
    if(packet->getType() != type) {
        delete packet;
        return nullptr;
    }

    return packet;
}

int Socket::testConnection(bool proposed) const {
    if(proposed) {
        if(receiveConnectionTest() == -1) return -1;
        return sendConnectionTest();
    } else {
        size_t requestSize = ConnectionTestRequestPacket().getSerializationSize();
        if(send(ConnectionTestRequestPacket()) != requestSize) return -1;
        int result = sendConnectionTest();
        if(result == -1) return -1;
        if(receiveConnectionTest() == -1) return -1;
        return result;
    }
}

std::string Socket::toString() const {
    return std::string(inet_ntoa(sockAddrIn.sin_addr)) + ":" + std::to_string(ntohs(sockAddrIn.sin_port));
}

int Socket::sendConnectionTest() const {
    size_t size = 16*1024*1024;
    char* buffer = new char[size];
    std::random_device random_device; // create object for seeding
    std::mt19937 engine{random_device()}; // create engine and seed it
    std::uniform_int_distribution<unsigned char> dist(0,255); // create distribution for integers with [1, 100000] range
    for(size_t i = 0; i < size; ++i)
        buffer[i] = static_cast<char>(dist(engine));

    DataPacket packet(buffer, size, false);
    if(send(packet) != packet.getSerializationSize()) return -1;

    SHA256 sha256;
    auto checkSum = sha256(buffer, size);

    auto* response = dynamic_cast<DataPacket*>(receive(Packet::Type::DATA));
    if(response == nullptr) return -1;

    if(checkSum != std::string(response->getData(), response->getDataSize())) return 1;
    return 2;
}

int Socket::receiveConnectionTest() const {
    auto* packet = dynamic_cast<DataPacket*>(receive(Packet::Type::DATA, false));
    if(packet == nullptr) return -1;

    SHA256 sha256;
    auto checkSum = sha256(packet->getData(), packet->getDataSize());

    delete packet;

    DataPacket response(checkSum.c_str(), checkSum.size(), false);
    if(send(response) != response.getSerializationSize()) return -1;

    return 2;
}