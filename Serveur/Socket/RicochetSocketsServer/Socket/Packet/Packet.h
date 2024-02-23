#ifndef RICOCHETSOCKETSSERVER_PACKET_H
#define RICOCHETSOCKETSSERVER_PACKET_H

#include <cstddef>


/**
 * @brief This class represents a packet of data sent through the network
 * @note This class is the base class for all the packets, a new packet should override all serialize and deserialize functions (if needed)
 */
class Packet {
public:
    /**
     * @brief This enum represents the type of the packet
     */
    enum class Type : unsigned char{
        EMPTY = 0,
        DATA = 1,
        CONNECTION_TEST_REQUEST = 2,
    };

    /**
     * @brief Constructor
     */
    Packet();

    /**
     * @brief Destructor
     */
    virtual ~Packet()= default;

    /**
     * @brief Get the type of the packet
     * @return The type of the packet
     */
    [[nodiscard]] Packet::Type getType() const;

    /**
     * @brief Get the serialization of the packet
     * @return The serialization of the packet
     * @note The serialization is a char* that can be sent through the network
     * @note The serialization is owned by the caller and should be deleted after use
     * @note The serialization always starts with : [size_t packetSize][Type type] and ends with the data buffer
     * @note The serialization is the concatenation of the serialization of the header and the data buffer, it is recommended to use serializeHeader and getData instead
     */
    [[nodiscard]] virtual char* serialize() const;

    /**
     * @brief Get the size of serialization of the packet
     * @return The size of serialization of the packet
     */
    [[nodiscard]] virtual size_t getSerializedSize() const;

    /**
     * @brief Get the serialization of the header of the packet, this is the serialization of the packet without the data buffer
     * @return The serialization of the header of the packet
     * @note The serialization is owned by the caller and should be deleted after use
     * @note The serialization always starts with : [size_t packetSize][Type type]
     */
    [[nodiscard]] virtual char* serializeHeader() const;

    /**
     * @brief Get the size of the serialization of the header of the packet
     * @return The size of the serialization of the header of the packet
     */
    [[nodiscard]] virtual size_t getSerializedHeaderSize() const;

    /**
     * @brief Deserialize the packet from the given serialization
     * @param serialized The serialization of the packet
     * @return The deserialized packet
     */
    static Packet::Type deserializeType(const char* serialized);

    /**
     * @brief Deserialize the packet from the given serialization
     * @param serialized The serialization of the packet
     * @return The deserialized packet, nullptr if the packet type is not recognized
     */
    [[nodiscard]] static Packet* deserialize(const char* serialized);

    /**
     * @brief Get the data of the packet
     * @return The data of the packet
     */
    [[nodiscard]] char* getData() const;

    /**
     * @brief Get the size of the data of the packet
     * @return The size of the data of the packet
     */
    [[nodiscard]] size_t getDataSize() const;

protected:
    /**
     * @brief Type of the packet
     */
    Type type;

    /**
     * @brief Data of the packet
     */
    char* data;

    /**
     * @brief Size of the data
     */
    size_t dataSize;
};


#endif //RICOCHETSOCKETSSERVER_PACKET_H
