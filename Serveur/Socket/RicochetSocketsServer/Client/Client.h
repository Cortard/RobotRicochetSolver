#ifndef RICOCHETSOCKETSSERVER_CLIENT_H
#define RICOCHETSOCKETSSERVER_CLIENT_H

#include <thread>
#include "../MultipleTypePointer/MultipleTypePointer.h"
#include "../Logs/Logs.h"
#include "../Socket/Socket.h"

/**
 * @brief A class to handle a client
 */
class Client {
public:

    /**
     * @brief Constructor of the class
     */
    Client();

    /**
     * @brief Start the process of the client
     * @param newSocket The socket client to use
     * @param newId The id of the client on the server
     */
    void startProcess(Socket* newSocket, unsigned int newId);

    /**
     * @brief Ask the client to stop
     */
    void askStop();

    /**
     * @brief Wait for the client to stop
     */
    void waitStop();

    /**
     * @brief Check if the client is busy
     * @return True if the client is busy, false otherwise
     */
    bool isBusy();

    /**
     * @brief Destructor of the class
     */
    ~Client();

private:
    /**
     * @brief The socket of the client
     */
    Socket* socket;
    /**
     * @brief The id of the client on the server
     */
    unsigned int id;
    /**
     * @brief A boolean to know if the client is busy
     */
    bool busy;
    /**
     * @brief A boolean to know if the client should stop
     */
    bool shouldStop;
    /**
     * @brief The thread of the process
     */
    std::thread processThread;

    /**
     * @brief The output of the current process phase
     */
    MultipleTypePointer output;

    /**
     * @brief Set up the client
     * @param newSocket The socket client to use
     * @param newId The id of the client on the server
     */
    void setUp(Socket* newSocket, unsigned int newId);

    /**
     * @brief The process of the client
     * @param newSocket The socket client to use
     * @param newId The id of the client on the server
     * @note This function is called by the startProcess function in the processThread
     * @note This function call the setUp and the processLoop functions
     */
    void process(Socket* newSocket, unsigned int newId);

    /**
     * @brief The loop of the process of the client
     */
    void processLoop();

};

#endif //RICOCHETSOCKETSSERVER_CLIENT_H
