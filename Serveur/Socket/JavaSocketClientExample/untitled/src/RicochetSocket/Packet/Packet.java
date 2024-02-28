package RicochetSocket.Packet;

/**
 * Packet class, used to represent a packet
 * This class is the base class for all the packets, a new packet type should be created by extending this class and implementing all serialize method
 */
public class Packet {
    /**
     * Packet type represents the type of the packet
     */
    public enum Type {
        EMPTY((byte)0),
        DATA((byte)1),
        CONNECTION_TEST_REQUEST((byte)2);

        private final byte value;

        Type(byte value) {
            this.value = value;
        }

        public byte getValue() {
            return value;
        }
    }

    /**
     * Packet type
     */
    protected Type type;
    /**
     * Packet data
     */
    protected byte[] data;

    /**
     * Constructor
     */
    public Packet() {
        this.type = Type.EMPTY;
        this.data = new byte[0];
    }

    /**
     * Get the packet type
     * @return Packet type
     */
    public Type getType() {
        return type;
    }

    /**
     * Serialize the packet
     * @return Serialized packet
     */
    public byte[] serialize() {
        long size = getSerializationSize();
        byte[] serialized = new byte[(int) size];

        byte[] header = serializeHeader();
        System.arraycopy(header, 0, serialized, 0, header.length);
        System.arraycopy(data, 0, serialized, header.length, data.length);

        return serialized;
    }

    /**
     * Get the size of the serialized packet
     * @return Serialized packet size
     */
    public long getSerializationSize() {
        return data.length + getHeaderSerializationSize();
    }

    /**
     * Serialize the packet header
     * @return Serialized header
     */
    byte[] serializeHeader() {
        long packetSize = getSerializationSize();
        long size = getHeaderSerializationSize();
        byte[] header = new byte[(int) size];
        for(int i = 0; i < 8; i++) {
            header[i] = (byte) ((packetSize >> (i * 8)) & 0xFF);
        }
        header[8] = (byte) type.getValue();
        return header;
    }

    /**
     * Get the size of the serialized header
     * @return Serialized header size
     */
    public long getHeaderSerializationSize() {
        return 8 + 1; // 8 bytes for the packet size and 1 byte for the packet type
    }

    /**
     * Deserialize the type of the packet
     * @param data Serialized packet
     * @return Deserialized packet type
     */
    public static Type deserializeType(byte[] data) {
        return  Type.values()[data[8]];
    }

    /**
     * Deserialize the packet
     * @param data Serialized packet
     * @return Deserialized packet
     */
    public static Packet deserialize(byte[] data) {
        Type type = deserializeType(data);
        if(type == Type.EMPTY) return new Packet();
        return null;
    }

    /**
     * Get the packet data
     * @return Packet data
     */
    public byte[] getData() {
        return data;
    }
}
