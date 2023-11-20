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

#define STATE_DISCONNECTED (-1)
#define STATE_CONNECTED 0

class Client {
private:
    SOCKET sock;
    int state;
public:
    Client();
    Client(SOCKET sock, int id);
    [[nodiscard]] SOCKET getSock() const;
    [[nodiscard]] int getState() const;
    void setState(int newState);
    void close() const;
};


#endif //STDSOCKETSSERVER_CLIENT_H
