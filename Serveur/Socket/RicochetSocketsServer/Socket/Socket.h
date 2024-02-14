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

/**
 * @brief This class is a wrapper for the socket system calls
 */
class Socket {
public:
    /**
     * @brief Initialize the class, the return value should not be ignored
     * @return 0 if the class was initialized successfully, -1 otherwise
     * @note This function must be called before any other function of this class
     * @note In reality, this function is called in the constructor of the class
     * @note This function calls WSAStartup on Windows, and does nothing on Linux
     */
    [[nodiscard]] static int init();
    /**
     * @brief End the class
     * @note This function must be called after all the other functions of this class
     * @note This function calls WSACleanup on Windows, and does nothing on Linux
     */
    static void end();

    /**
     * @brief Create a server socket and bind it to the given ip and port
     * @param ip The ip to bind the socket to
     * @param port The port to bind the socket to
     * @note This function calls socket, setsockopt, bind and listen
     * @note This function throws a std::runtime_error if any of the system calls fail
     */
    Socket(const char* ip, unsigned short port);

    /**
     * @brief Create a client socket from the given socket and address
     * @param sock The socket to create the client socket from
     * @param addressInternet The address to create the client socket from
     */
    Socket(SOCKET sock, SOCKADDR_IN addressInternet);

    /**
     * @brief Accept a client socket from a server socket, the return value should not be ignored
     * @return A pointer to the client socket if the system call accept is successful, nullptr otherwise
     */
    [[nodiscard]] Socket* accept() const;

    /**
     * @brief Send a buffer of a given length, the return value should not be ignored
     * @param buffer The buffer to send
     * @param length The length of the buffer
     * @return The number of bytes sent
     */
    [[nodiscard]] size_t send(const char* buffer, int length) const;

    /**
     * @brief Receive a buffer of a given length, the return value should not be ignored
     * @param buffer The buffer to receive
     * @param length The length of the buffer
     * @return The number of bytes received
     */
    [[nodiscard]] size_t receive(char* buffer, int length) const;

    /**
     * @brief Convert the socket to a string, the return value should not be ignored
     * @return The string representation of the socket in the form "ip:port"
     */
    [[nodiscard]] std::string toString() const;

    /**
     * @brief Destroy the socket
     */
    ~Socket();

private:
    /**
     * @brief boolean to check if the class is initialized
     */
    static bool isClassInit;

    /**
     * @brief The value to set the SO_REUSEADDR option to (SO_REUSEADDR is used to allow to reuse the same address immediately after the socket is closed)
     */
    static int True;//For setsockopt

    /**
     * @brief The socket
     */
    SOCKET sock;
    /**
     * @brief The internet address
     */
    SOCKADDR_IN sockAddrIn;
};

#endif //RICOCHETSOCKETSSERVER_SOCKET_H
