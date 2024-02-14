#ifndef RICOCHETSOCKETSSERVER_SERVER_H
#define RICOCHETSOCKETSSERVER_SERVER_H

#include <thread>
#include "../config.h"
#include "../Client/Client.h"
#include "../Logs/Logs.h"
#include "../Socket/Socket.h"

/**
 * @brief Server class
 */
class Server {
public:
    /**
     * @brief Run the server
     * @return 0 if the server ran successfully
     */
    static int run();
    /**
     * @brief Stop the server, can be called on signal handler
     */
    static void stop();

private:
    /**
     * @brief Server running status
     */
    static bool running;

    /**
     * @brief Server socket
     */
    static Socket* socket;

    /**
     * @brief Clients slots
     * @note Clients are stored in an array
     */
    static Client clients[MAX_CLIENTS];

    /**
     * @brief Next client id
     * @note Used to identify clients
     */
    static unsigned int nextClientId;

    /**
     * @brief Server initialization
     * @return 0 if the server initialized successfully
     * @note Create the server socket
     */
    static int init();

    /**
     * @brief Server loop
     * @note Accept clients and handle them
     */
    static void loop();

    /**
     * @brief Find an empty slot for a new client
     * @return The slot index if found, -1 otherwise
     */
    static int foundEmptySlot();
};


#endif //RICOCHETSOCKETSSERVER_SERVER_H
