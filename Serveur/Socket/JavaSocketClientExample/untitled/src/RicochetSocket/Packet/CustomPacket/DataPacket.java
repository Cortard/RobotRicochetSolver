package RicochetSocket.Packet.CustomPacket;

import RicochetSocket.Packet.Packet;

/**
 * Data packet class, used to represent a data packet
 */
public class DataPacket extends Packet {
    /**
     * Constructor
     */
    public DataPacket() {
        super();
        this.type = Type.DATA;
    }

    /**
     * Constructor
     * @param data Data
     */
    public DataPacket(byte[] data) {
        this.type = Type.DATA;
        this.data = data;
    }

    /**
     * Deserialize the packet
     * @param data Serialized packet
     */
    public static DataPacket deserialize(byte[] data) {
        Type type = deserializeType(data);
        if(type!=Type.DATA) return null;

        DataPacket dataPacket = new DataPacket();
        long size = 0;
        for(int i = 0; i < 8; i++) {
            size |= (long) (data[i] & 0xFF) << (i * 8);
        }
        long dataSize = size - dataPacket.getHeaderSerializationSize();
        dataPacket.data = new byte[(int) dataSize];
        System.arraycopy(data, 9, dataPacket.data, 0, (int) dataSize);
        return dataPacket;
    }
}