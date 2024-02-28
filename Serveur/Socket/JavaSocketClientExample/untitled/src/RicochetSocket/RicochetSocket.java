package RicochetSocket;

import RicochetSocket.Packet.CustomPacket.ConnectionTestRequestPacket;
import RicochetSocket.Packet.CustomPacket.DataPacket;
import RicochetSocket.Packet.CustomPacket.PacketDeserializer;
import RicochetSocket.Packet.Packet;

import java.net.InetSocketAddress;
import java.net.Socket;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * RicochetSocket is a class that represents a socket that can be used to send and receive packets.
 */
public class RicochetSocket {
    /**
     * The socket that is used to send and receive packets.
     */
    private final Socket socket;
    /**
     * A boolean that represents if the socket is connected or not.
     */
    private boolean isConnected;

    /**
     * Constructor for RicochetSocket.
     */
    public RicochetSocket() {
        this.socket = new Socket();
        this.isConnected = false;
    }

    /**
     * Connects the socket to the server.
     * @param local a boolean that represents if the connection is local or not.
     * @return true if the socket is connected, false otherwise.
     */
    public boolean connect(boolean local) {
        try {
            String serverIp;
            if(local) serverIp = "127.0.0.1";
            else serverIp = "195.201.205.241";
            int serverPort = 9090;
            this.socket.connect(new InetSocketAddress(serverIp, serverPort));
            this.isConnected = true;
            return true;
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
        return false;
    }

    /**
     * Connects the socket to the server. Calls connect(boolean) with local set to false.
     * @return true if the socket is connected, false otherwise.
     * @see #connect(boolean)
     */
    public boolean connect() {
        return connect(false);
    }

    /**
     * Disconnects the socket from the server.
     */
    public void disconnect() {
        if (this.isConnected) {
            try {
                this.socket.close();
                this.isConnected = false;
            } catch (Exception e) {
                System.out.println("Error: " + e);
            }
        }
    }

    /**
     * Sends a packet to the server.
     * @param packet the packet to be sent.
     * @return true if the packet was sent, false otherwise.
     */
    public boolean send(Packet packet) {
        if (this.isConnected) {
            try {
                byte[] serialized = packet.serialize();
                socket.getOutputStream().write(serialized);
                return true;
            } catch (Exception e) {
                System.out.println("Error: " + e);
            }
        }
        return false;
    }

    /**
     * Receives a packet from the server.
     * @param acceptConnectionTest a boolean that represents if a potential connection test packet should be accepted.
     * @return the packet that was received, or null if no packet was received.
     */
    public Packet receive(boolean acceptConnectionTest) {
        if (this.isConnected) {
            try {
                byte[] buffer = new byte[8];
                socket.getInputStream().read(buffer);
                long size = 0;
                for (int i = 0; i < 8; i++) {
                    size |= (long) (buffer[i] & 0xFF) << (i * 8);
                }

                byte[] data = new byte[(int) size];
                System.arraycopy(buffer, 0, data, 0, 8);
                socket.getInputStream().read(data, 8, (int) size - 8);

                Packet packet = PacketDeserializer.deserialize(data);
                if(packet==null) return null;

                if(acceptConnectionTest && packet.getType() == Packet.Type.CONNECTION_TEST_REQUEST) {
                    //TODO: Send ConnectionTestResponsePacket
                    return null;
                }

            } catch (Exception e) {
                System.out.println("Error: " + e);
            }
        }
        return null;
    }

    /**
     * Receives a packet from the server.
     * @return the packet that was received, or null if no packet was received.
     * @see #receive(boolean)
     */
    public Packet receive() {
        return receive(false);
    }

    /**
     * Receives a packet from the server. Calls receive(boolean) and checks if the received packet is of the expected type.
     * @param type the type of packet that is expected.
     * @param acceptConnectionTest a boolean that represents if a potential connection test packet should be accepted.
     * @return the packet that was received, or null if no packet was received.
     * @see #receive(boolean)
     */
    public Packet receive(Packet.Type type, boolean acceptConnectionTest) {
        Packet packet = receive(acceptConnectionTest);
        if(packet==null) return null;
        if(acceptConnectionTest && packet.getType() == Packet.Type.CONNECTION_TEST_REQUEST) {
            return packet;
        }
        if(packet.getType() == type) {
            return packet;
        }
        return null;
    }

    /**
     * Receives a packet from the server. Calls receive(Packet.Type, boolean) with acceptConnectionTest set to false.
     * @param type the type of packet that is expected.
     * @return the packet that was received, or null if no packet was received.
     * @see #receive(Packet.Type, boolean)
     */
    public Packet receive(Packet.Type type) {
        return receive(type, false);
    }


    /**
     * Test the connection with the server.
     * @param proposed a boolean that represents if the test is proposed or not.
     * @return -1 if the connection is not successful, 1 if the connection is bad and 2 if the connection is successful
     */
    public int testConnection(boolean proposed) {
        if(proposed) {
            if(receiveConnectionTest()==-1) return -1;
            return sendConnectionTest();
        }else {
            if(!send(new ConnectionTestRequestPacket())) return -1;
            int result = sendConnectionTest();
            if(result==-1) return -1;
            if(receiveConnectionTest()==-1) return -1;
            return result;
        }
    }

    /**
     * Test the connection with the server.
     * @return -1 if the connection is not successful, 1 if the connection is bad and 2 if the connection is successful
     * @see #testConnection(boolean)
     */
    public int testConnection() {
        return testConnection(false);
    }

    /**
     * Sends a connection test to the server.
     * @return -1 if the connection is not successful, 1 if the connection is bad and 2 if the connection is successful
     */
    public int sendConnectionTest() {
        long size = 16*1024*1024;
        byte[] data = new byte[(int) size];
        for(int i = 0; i < size; i++) {
            data[i] = (byte) (Math.random() * 256);
        }

        DataPacket dataPacket = new DataPacket(data);
        if(!send(dataPacket)) return -1;

        byte[] hash;
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            hash = digest.digest(data);
        } catch (NoSuchAlgorithmException e) {
            System.out.println("Error: " + e);
            return -1;
        }

        DataPacket response = (DataPacket) receive(Packet.Type.DATA);
        if(response==null) return -1;

        if(response.getData().length!=hash.length) return -1;
        for(int i = 0; i < hash.length; i++) {
            if(response.getData()[i]!=hash[i]) return 1;
        }
        return 2;
    }

    /**
     * Receives a connection test from the server.
     * @return -1 if the connection is not successful and 2 if the connection is successful
     */
    public int receiveConnectionTest() {
        DataPacket dataPacket = (DataPacket) receive(Packet.Type.DATA);
        if(dataPacket==null) return -1;

        byte[] hash;
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            hash = digest.digest(dataPacket.getData());
        } catch (NoSuchAlgorithmException e) {
            System.out.println("Error: " + e);
            return -1;
        }

        DataPacket response = new DataPacket(hash);
        if(!send(response)) return -1;

        return 2;
    }

    /**
     * Returns the socket.
     * @return the socket.
     */
    @Override
    public String toString() {
        return "RicochetSocket{" +
                "socket=" + socket +
                ", isConnected=" + isConnected +
                '}';
    }
}
