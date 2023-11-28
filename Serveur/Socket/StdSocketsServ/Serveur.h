#ifndef STDSOCKETSSERVER_SERVEUR_H
#define STDSOCKETSSERVER_SERVEUR_H

#include <thread>
#include "clients/Client.h"
#include "configue.h"


class Serveur {
public:
    static Client slots[MAX_CLIENTS];

    static int init();
    static void end();

    static void acceptLoop();
    static void processLoop();
private:
    static SOCKET sock;
    static SOCKADDR_IN addressInternet;

    static int foundEmptySlot();

    template <typename T>
    static int verifySocketOutput(Client* slot, bool send, int result);

    static void getClientDataType(Client* slot);
    static void confirmClientDataType(Client* slot);

    static void getClientPictureSize(Client* slot);
    static void confirmClientPictureSize(Client* slot);
    static void getClientPicture(Client* slot);
    static void confirmClientPicture(Client* slot);
};


#endif //STDSOCKETSSERVER_SERVEUR_H
