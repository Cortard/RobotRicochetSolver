#ifndef STDSOCKETSSERVER_SERVER_H
#define STDSOCKETSSERVER_SERVER_H

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

#include <thread>

#define IP "127.0.0.1"
#define PORT 9090
#define MAX_CLIENTS 5

class Server {
public:
    static int run();
    static void stop();

private:
    static bool running;
    static SOCKET sock;
    static SOCKADDR_IN addressInternet;

    static int init();
    static void loop();
};


#endif //STDSOCKETSSERVER_SERVER_H
