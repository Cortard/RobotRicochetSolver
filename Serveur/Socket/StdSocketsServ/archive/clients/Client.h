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
#include "../../configue.h"
#include "../logs/Logs.h"

// if state is odd, the slot is processing or disconnected
#define STATE_DISCONNECTED (-1)
#define STATE_NEW_CONNECTED 0
#define STATE_RECEIVING_TYPE_DATA 1
#define STATE_RECEIVED_TYPE_DATE 2
#define STATE_SENDING_TYPE_DATA_CONFIRMATION 3
#define STATE_SENT_TYPE_DATA_CONFIRMATION 4

//Case receive picture
#define STATE_RECEIVING_PICTURE_SIZE 101
#define STATE_RECEIVED_PICTURE_SIZE 102
#define STATE_SENDING_PICTURE_SIZE_CONFIRMATION 103
#define STATE_SENT_PICTURE_SIZE_CONFIRMATION 104
#define STATE_RECEIVING_PICTURE 105
#define STATE_RECEIVED_PICTURE 106
#define STATE_SENDING_PICTURE_CONFIRMATION 107
#define STATE_SENT_TYPE_PICTURE_CONFIRMATION 108
#define STATE_BUILDING_BOARD 109
#define STATE_BUILT_BOARD 110
#define STATE_RECEIVING_NB_ROBOTS 111
#define STATE_RECEIVED_NB_ROBOTS 112
#define STATE_SENDING_NB_ROBOTS_CONFIRMATION 113
#define STATE_SENT_NB_ROBOTS_CONFIRMATION 114
#define STATE_RECEIVING_ROBOTS 115
#define RECEIVED_ROBOTS 116
#define RECEIVING_TOKEN 117
#define RECEIVED_TOKEN 118


//Case receive grid
#define STATE_RECEIVING_GRIP_TYPE 201
#define STATE_RECEIVED_GRIP_TYPE 202
#define STATE_SENDING_GRIP_TYPE_CONFIRMATION 203
#define STATE_SENT_TYPE_GRIP_TYPE_CONFIRMATION 204
#define STATE_RECEIVING_GRID 205
#define STATE_RECEIVED_GRID 206

//Process
#define STATE_SENDING_PROCESS_TIME 301
#define STATE_SENT_TYPE_PROCESS_TIME 302
#define STATE_PREPARING_GRID 303
#define STATE_PREPARED_GRID 304
#define STATE_SOLVING 305
#define STATE_SOLVED 306
#define STATE_SENDING_PATH 307
#define STATE_SENT_TYPE_PATH 308
#define STATE_SENDING_GRID 309
#define STATE_SENT_GRID 310

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
