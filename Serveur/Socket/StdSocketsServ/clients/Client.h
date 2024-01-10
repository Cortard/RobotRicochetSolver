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
#include <thread>
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
#define STATE_RECEIVING_GRIP_TYPE 21
#define STATE_RECEIVED_GRIP_TYPE 22
#define STATE_SENDING_GRIP_TYPE_CONFIRMATION 23
#define STATE_SENT_TYPE_GRIP_TYPE_CONFIRMATION 24
#define STATE_RECEIVING_GRID 25
#define STATE_RECEIVED_GRID 26
#define STATE_SENDING_GRID_CONFIRMATION 27
#define STATE_SENT_TYPE_GRID_CONFIRMATION 28

//Process
#define STATE_SOLVING 51
#define STATE_SOLVED 52
#define STATE_SENDING_PATH 53
#define STATE_SENT_TYPE_PATH 54

#define STATE_Process1 98

class Client {
private:
    static int nextIdSlot;
public:
    int slotNum;
    std::thread processThread;
    int state;
    SOCKET socket;
    void *output;

    Client();
    void connect(SOCKET client);
    template <typename T>
    void clearOutput();

    void disconnect();
    ~Client();
};


#endif //STDSOCKETSSERVER_CLIENT_H
