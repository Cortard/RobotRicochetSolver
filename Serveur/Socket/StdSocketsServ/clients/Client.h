#ifndef STDSOCKETSSERVER_CLIENT_H
#define STDSOCKETSSERVER_CLIENT_H

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close (s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <mutex>
#include <stdexcept>
#include "../configue.h"
#include "../logs/Logs.h"

// if state is odd, the slot is processing or disconnected
#define STATE_DISCONNECTED (-1)
#define STATE_NEW_CONNECTED 0
#define STATE_RECEIVING_TYPE_DATA 1
#define STATE_RECEIVED_TYPE_DATE 2
#define STATE_SENDING_TYPE_DATA_CONFIRMATION 3
#define STATE_SENT_TYPE_DATA_CONFIRMATION 4

//Case receive picture
#define STATE_RECEIVING_PICTURE_SIZE 5
#define STATE_RECEIVED_PICTURE_SIZE 6
#define STATE_SENDING_PICTURE_SIZE_CONFIRMATION 7
#define STATE_SENT_PICTURE_SIZE_CONFIRMATION 8
#define STATE_RECEIVING_PICTURE 9
#define STATE_RECEIVED_PICTURE 10
#define STATE_SENDING_PICTURE_CONFIRMATION 11
#define STATE_SENT_TYPE_PICTURE_CONFIRMATION 12

//Case receive grid
#define STATE_RECEIVING_GRIP_TYPE 13
#define STATE_RECEIVED_GRIP_TYPE 14
#define STATE_SENDING_GRIP_TYPE_CONFIRMATION 15
#define STATE_SENT_TYPE_GRIP_TYPE_CONFIRMATION 16
#define STATE_RECEIVING_GRID 17
#define STATE_RECEIVED_GRID 18
#define STATE_SENDING_GRID_CONFIRMATION 19
#define STATE_SENT_TYPE_GRID_CONFIRMATION 20

//Process
#define STATE_Process1 19

class Client {
private:
    static int nextIdSlot;
public:
    std::mutex mutex;
    int slotNum;
    int state;
    SOCKET socket;
    void* output;

    Client();
    void connect(SOCKET client);
    template <typename T>
    void clearOutput();

    void disconnect();
    ~Client();
};


#endif //STDSOCKETSSERVER_CLIENT_H
