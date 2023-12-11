#ifndef STDSOCKETSSERVER_SERVEUR_H
#define STDSOCKETSSERVER_SERVEUR_H

#include <thread>
#include "solver/Solver.h"
#include "clients/Client.h"
#include "configue.h"


class Serveur {
public:
    static Client slots[MAX_CLIENTS];

    static int init();
    static void end();

    [[noreturn]] static void acceptLoop();

    [[noreturn]] static void processLoop();
private:
    static SOCKET sock;
    static SOCKADDR_IN addressInternet;
    static std::chrono::seconds lastProcessTime;

    static int foundEmptySlot();

    template <typename T>
    static int verifySocketOutput(Client* slot, bool send, int result);

    static void getClientDataType(Client* slot);
    static void confirmClientDataType(Client* slot);

    //Picture
    static void getClientPictureSize(Client* slot);
    static void confirmClientPictureSize(Client* slot);
    static void getClientPicture(Client* slot);
    static void confirmClientPicture(Client* slot);

    //Grid
    static void getClientGridType(Client* slot);
    static void confirmClientGridType(Client* slot);
    static void getClientGrid(Client* slot);
    static void confirmClientGrid(Client* slot);

    //Process
    static void solving(Client* slot);
    static bool callbackSolver(unsigned int max_depth, std::chrono::seconds duration);
    static void sendPath(Client* slot);
};


#endif //STDSOCKETSSERVER_SERVEUR_H
