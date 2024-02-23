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
    ConnectionTestRequestPacket(){
        this->type = Packet::Type::CONNECTION_TEST_REQUEST;
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
     * @brief Set the result of the connection test
     * @param result The result of the connection test
     */
    void setResult(int newResult){
        this->result = newResult;
    }

    /**
     * @brief Get the result of the connection test
     * @return The result of the connection test
     */
    [[nodiscard]] int getResult() const{
        return result;
    }

private:
    int result=0;
};

#endif //RICOCHETSOCKETSSERVER_CONNECTION_TEST_REQUEST_PACKET_H
