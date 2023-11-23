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

class Client {
public:
    std::mutex mutex;
    int state;
    SOCKET socket;
    void* output;

    Client();
    void connect(SOCKET socket);
    void disconnect();
    ~Client();
};


#endif //STDSOCKETSSERVER_CLIENT_H
