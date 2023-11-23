#ifndef STDSOCKETSSERVER_SERVEUR_H
#define STDSOCKETSSERVER_SERVEUR_H

#include <thread>
#include "clients/Client.h"
#include "configue.h"


class Serveur {
private:
    static SOCKET sock;
    static SOCKADDR_IN addressInternet;

    static int foundEmptySlot();
    static void getTypeDataClient(Client* slot);
    static void confirmTypeDataClient(Client* slot);
public:
    static Client slots[MAX_CLIENTS];

    static int init();
    static void close();

    static void acceptLoop();
    static void processLoop();
};


#endif //STDSOCKETSSERVER_SERVEUR_H
