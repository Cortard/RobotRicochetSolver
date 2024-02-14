#ifndef RICOCHETSOCKETSSERVER_SERVER_H
#define RICOCHETSOCKETSSERVER_SERVER_H

#include <thread>
#include "../config.h"
#include "../Client/Client.h"
#include "../Logs/Logs.h"
#include "../Socket/Socket.h"

class Server {
public:
    static int run();
    static void stop();

private:
    static bool running;
    static Socket* socket;

    static Client clients[MAX_CLIENTS];
    static unsigned int nextClientId;

    static int init();
    static void loop();

    static int foundEmptySlot();
};


#endif //RICOCHETSOCKETSSERVER_SERVER_H
