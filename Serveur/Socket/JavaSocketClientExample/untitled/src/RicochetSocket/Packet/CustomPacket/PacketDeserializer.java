package RicochetSocket.Packet.CustomPacket;

import RicochetSocket.Packet.Packet;

/**
 * Packet deserializer class, used to deserialize a packet
 */
public class PacketDeserializer {
    /**
     * Deserialize a packet
     * @param data Serialized packet
     * @return Deserialized packet
     */
    public static RicochetSocket.Packet.Packet deserialize(byte[] data) {
        RicochetSocket.Packet.Packet.Type type = RicochetSocket.Packet.Packet.deserializeType(data);
        return switch (type) {
            case EMPTY -> Packet.deserialize(data);
            case DATA -> DataPacket.deserialize(data);
            case CONNECTION_TEST_REQUEST -> ConnectionTestRequestPacket.deserialize(data);
            default -> null;
        };
    }
}
