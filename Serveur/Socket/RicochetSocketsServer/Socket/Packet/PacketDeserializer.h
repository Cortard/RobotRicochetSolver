#ifndef RICOCHETSOCKETSSERVER_PACKET_DESERIALIZER_H
#define RICOCHETSOCKETSSERVER_PACKET_DESERIALIZER_H

#include "Packet.h"
#include "CustomPacket/DataPacket.h"
#include "CustomPacket/ConnectionTestRequestPacket.h"

/**
 * @brief This class is a helper to deserialize a packet
 */
class PacketDeserializer {
public:
    /**
     * @brief Deserialize the packet from the given serialization
     * @param serialized The serialization of the packet
     * @return The deserialized packet
     */
    static Packet* deserialize(const char* serialized){
        Packet::Type type = Packet::deserializeType(serialized);
        switch(type) {
            case Packet::Type::EMPTY :
                return Packet::deserialize(serialized);
            case Packet::Type::DATA :
                return DataPacket::deserialize(serialized);
            case Packet::Type::CONNECTION_TEST_REQUEST :
                return ConnectionTestRequestPacket::deserialize(serialized);
            default:
                return nullptr;
        }
    }
};

#endif //RICOCHETSOCKETSSERVER_PACKET_DESERIALIZER_H
