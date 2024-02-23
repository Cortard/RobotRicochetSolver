#include "DataPacket.h"

#include <cstring>

DataPacket::DataPacket() : Packet(), isOwner(true) {
    this->type = Type::DATA;
    this->data = nullptr;
    this->dataSize = 0;
}

DataPacket::DataPacket(const char* data, size_t size, bool isOwner) : Packet(), isOwner(isOwner){
    this->type = Type::DATA;
    this->data = new char[size];
    memcpy(this->data, data, size);
    this->dataSize = size;
}

DataPacket::~DataPacket() {
    if(isOwner) delete[] data;
}

DataPacket* DataPacket::deserialize(const char* serialized) {
    Type type = deserializeType(serialized);
    if(type != Type::DATA) return nullptr;

    auto* packet = new DataPacket();
    size_t size = *reinterpret_cast<const size_t*>(serialized);
    packet->dataSize = size - sizeof(size_t) - sizeof(Type);
    packet->data = new char[packet->dataSize];
    memcpy(packet->data, serialized + sizeof(size_t) + sizeof(Type), packet->dataSize);
    packet->isOwner = true;

    return packet;
}