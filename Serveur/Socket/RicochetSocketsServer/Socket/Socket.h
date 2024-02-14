#ifndef RICOCHETSOCKETSSERVER_SOCKET_H
#define RICOCHETSOCKETSSERVER_SOCKET_H

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #define INVALID_SOCKET (-1)
    #define SOCKET_ERROR (-1)
    #define closesocket(s) close (s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <cstdlib>
#include <stdexcept>

class Socket {
private:
    static bool isClassInit;
    static int True;//For setsockopt

    SOCKET sock;
    SOCKADDR_IN sockAddrIn;

public:
    [[nodiscard]] static int init();
    static void clear();

    Socket(const char* ip, unsigned short port);
    Socket(SOCKET sock, SOCKADDR_IN addressInternet);
    ~Socket();

    [[nodiscard]] Socket* accept() const;

    [[nodiscard]] size_t send(const char* buffer, int length) const;
    [[nodiscard]] size_t receive(char* buffer, int length) const;

    [[nodiscard]] std::string toString() const;

    [[maybe_unused]] [[nodiscard]] SOCKET getSock() const;

    [[maybe_unused]] [[nodiscard]] SOCKADDR_IN getAddressInternet() const;
};

#endif //RICOCHETSOCKETSSERVER_SOCKET_H
