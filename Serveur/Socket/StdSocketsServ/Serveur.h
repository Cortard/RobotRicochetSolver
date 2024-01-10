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

    static void processLoop(Client* slot);
private:
    static SOCKET sock;
    static SOCKADDR_IN addressInternet;
    static std::chrono::seconds lastProcessTime;

    static int foundEmptySlot();

    template <typename T>
    static int verifySocketOutput(Client* slot, bool send, int result);

    static bool getClientDataType(Client* slot);
    static bool confirmClientDataType(Client* slot);

    //Picture
    static bool getClientPictureSize(Client* slot);
    static bool confirmClientPictureSize(Client* slot);
    static bool getClientPicture(Client* slot);
    static bool confirmClientPicture(Client* slot);

    //Grid
    static bool getClientGridType(Client* slot);
    static bool confirmClientGridType(Client* slot);
    static bool getClientGrid(Client* slot);
    static bool confirmClientGrid(Client* slot);

    //Process
    static bool solving(Client* slot);
    static bool callbackSolver(unsigned int max_depth, std::chrono::seconds duration);
    static bool sendPath(Client* slot);
};


#endif //STDSOCKETSSERVER_SERVEUR_H
