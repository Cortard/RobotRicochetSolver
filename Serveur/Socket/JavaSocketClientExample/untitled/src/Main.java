import RicochetSocket.Packet.CustomPacket.ConnectionTestRequestPacket;
import RicochetSocket.Packet.Packet;
import RicochetSocket.RicochetSocket;

public class Main {
    public static void main(String[] args) {
        RicochetSocket socket = new RicochetSocket();
        socket.connect(true);

        System.out.printf("Sent connection test result : %d\n", socket.testConnection());

        ConnectionTestRequestPacket packet = (ConnectionTestRequestPacket) socket.receive(Packet.Type.CONNECTION_TEST_REQUEST, true);
        if(packet == null) {
            System.out.println("Failed to receive packet");
            return;
        }
        System.out.println("Result from connection test: " + packet.getResult());

        socket.disconnect();
    }
}