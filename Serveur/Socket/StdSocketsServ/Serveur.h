#ifndef STDSOCKETSSERVER_SERVEUR_H
#define STDSOCKETSSERVER_SERVEUR_H

#include <thread>
#include "solver/Solver.h"
#include "clients/Client.h"
#include "configue.h"
#include "jpegBuilder/jpegBuilder.h"
#include "boardBuilder/board.h"
#include "boardBuilder/boardBuilder.h"
#include "boardIsolation/boardIsolation.h"

#define MAX_PICTURE_SIZE 1000000000

class Serveur {
public:
    static Client slots[MAX_CLIENTS];

    static int init();
    static void end();

    static void acceptLoop();

    static void processLoop(Client* slot);
private:
    static SOCKET sock;
    static SOCKADDR_IN addressInternet;
    static std::chrono::seconds totalProcessTime;
    static unsigned int totalNbProcess;
    static std::mutex mutexProcessTime;
    static bool running;
    static std::mutex mutexRunning;

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
    static bool buildBoard(Client* slot);
    static bool getClientNbRobots(Client* slot);
    static bool confirmClientNbRobots(Client* slot);
    static bool getClientRobots(Client* slot);
    static bool getClientToken(Client* slot);

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
