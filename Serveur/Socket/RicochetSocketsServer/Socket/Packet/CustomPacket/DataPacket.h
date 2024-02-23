#ifndef RICOCHETSOCKETSSERVER_DATA_PACKET_H
#define RICOCHETSOCKETSSERVER_DATA_PACKET_H

#include "../Packet.h"

/**
 * @brief This class represents a data packet
 */
class DataPacket : public Packet {
public:
    /**
     * @brief Constructor
     */
    DataPacket();

    /**
     * @brief Constructor
     * @param data The data to send
     * @param size The dataSize of the data
     */
    DataPacket(const char* data, size_t size, bool isOwner = true);

    /**
     * @brief Destructor
     */
    ~DataPacket() override;

    /**
     * @brief Deserialize the packet from the given serialization
     * @param serialized The serialization of the packet
     * @return The deserialized packet
     */
    static DataPacket* deserialize(const char* serialized);

private:
    /**
     * @brief If the packet is the owner of the data
     */
    bool isOwner;
};


#endif //RICOCHETSOCKETSSERVER_DATA_PACKET_H
