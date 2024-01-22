#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include "board.h"

class SocketConnection {
public:
    SocketConnection();
    static int getSolution(Board* board);
};

#endif // SOCKETCONNECTION_H
