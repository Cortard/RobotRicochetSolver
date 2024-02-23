#include <cstring>
#include "Packet.h"

Packet::Packet() : type(Type::EMPTY), data(nullptr), dataSize(0) {
}

Packet::Type Packet::getType() const {
    return type;
}

char* Packet::serialize() const{
    size_t serializedPacketSize = getSerializedSize();
    char* serializedHeader = serializeHeader();

    char* serialized = new char[serializedPacketSize];
    memcpy(serialized, serializedHeader, getSerializedHeaderSize());
    delete[] serializedHeader;

    memcpy(serialized + getSerializedHeaderSize(), data, dataSize);

    return serialized;
}

size_t Packet::getSerializedSize() const{
    return getSerializedHeaderSize() + dataSize;
}

char* Packet::serializeHeader() const {
    size_t serializedPacketSize = sizeof(size_t) + sizeof(type);
    char* serialized = new char[serializedPacketSize];
    char* dest = serialized;
    *reinterpret_cast<size_t*>(dest) = getSerializedSize();
    dest += sizeof(size_t);
    *reinterpret_cast<Type*>(dest) = type;
    return serialized;
}

size_t Packet::getSerializedHeaderSize() const {
    return sizeof(size_t) + sizeof(type);
}

Packet::Type Packet::deserializeType(const char* serialized) {
    return *reinterpret_cast<const Packet::Type*>(serialized + sizeof(size_t));
}

Packet* Packet::deserialize(const char* serialized) {
    Packet::Type type = Packet::deserializeType(serialized);
    if(type == Packet::Type::EMPTY) return new Packet();
    return nullptr;
}

char* Packet::getData() const {
    return data;
}

size_t Packet::getDataSize() const {
    return dataSize;
}