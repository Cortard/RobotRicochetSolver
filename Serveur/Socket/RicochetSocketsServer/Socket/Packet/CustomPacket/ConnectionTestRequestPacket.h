#ifndef RICOCHETSOCKETSSERVER_CONNECTION_TEST_REQUEST_PACKET_H
#define RICOCHETSOCKETSSERVER_CONNECTION_TEST_REQUEST_PACKET_H

#include "../Packet.h"

/**
 * @brief This class represents a connection test request packet
 */
class ConnectionTestRequestPacket : public Packet {
public:
    /**
     * @brief Constructor
     */
    ConnectionTestRequestPacket() : Packet() {
        this->type = Packet::Type::CONNECTION_TEST_REQUEST;
        this->result = 0;
    }

    /**
     * @brief Deserialize the packet from the given serialization
     * @param serialized The serialization of the packet
     * @return
     */
    static ConnectionTestRequestPacket* deserialize(const char* serialized){
        Packet::Type type = Packet::deserializeType(serialized);
        if(type != Packet::Type::CONNECTION_TEST_REQUEST) return nullptr;
        return new ConnectionTestRequestPacket();
    }

    /**
     * @brief Get the result of the connection test
     * @return The result of the connection test
     */
    [[nodiscard]] int getResult() const{
        return result;
    }

    /**
     * @brief Set the result of the connection test
     * @param result The result of the connection test
     */
    void setResult(int newResult){
        this->result = newResult;
    }

private:
    int result;
};

#endif //RICOCHETSOCKETSSERVER_CONNECTION_TEST_REQUEST_PACKET_H
