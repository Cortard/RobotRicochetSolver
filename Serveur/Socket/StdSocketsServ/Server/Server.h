#ifndef RICOCHETSOCKETSSERVER_SERVER_H
#define RICOCHETSOCKETSSERVER_SERVER_H

#include <thread>
#include "../configue.h"
#include "../Client/Client.h"
#include "../Logs/Logs.h"
#include "../socket.h"

class Server {
public:
    static int run();
    static void stop();

private:
    static bool running;
    static SOCKET sock;
    static SOCKADDR_IN addressInternet;

    static Client* clients[MAX_CLIENTS];
    static unsigned int nextClientId;

    static int init();
    static void loop();

    static int foundEmptySlot();
};


#endif //RICOCHETSOCKETSSERVER_SERVER_H
