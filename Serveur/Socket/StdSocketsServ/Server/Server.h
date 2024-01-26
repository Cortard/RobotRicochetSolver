#ifndef STDSOCKETSSERVER_SERVER_H
#define STDSOCKETSSERVER_SERVER_H

#include <thread>
#include "../socket.h"
#include "../Client/Client.h"

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

    static Client* clients[MAX_CLIENTS];

    static int init();
    static void loop();

    static int foundEmptySlot();
};


#endif //STDSOCKETSSERVER_SERVER_H
