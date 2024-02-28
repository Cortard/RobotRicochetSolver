package RicochetSocket.Packet.CustomPacket;

/**
 * ConnectionTestRequestPacket class, used to represent a connection test request packet
 * This class is used to create a connection test request packet
 */
public class ConnectionTestRequestPacket extends RicochetSocket.Packet.Packet {
    /**
     * Result of the connection test
     */
    private int result;

    /**
     * Constructor
     */
    public ConnectionTestRequestPacket() {
        super();
        this.type = Type.CONNECTION_TEST_REQUEST;
    }

    /**
     * Deserialize the packet
     * @param data Serialized packet
     */
    public static ConnectionTestRequestPacket deserialize(byte[] data) {
        Type type = deserializeType(data);
        if(type!=Type.CONNECTION_TEST_REQUEST) return null;

        return new ConnectionTestRequestPacket();
    }

    /**
     * Getter of result
     * @return Result
     */
    public int getResult() {
        return result;
    }

    /**
     * Setter of result
     * @param result Result
     */
    public void setResult(int result) {
        this.result = result;
    }
}
