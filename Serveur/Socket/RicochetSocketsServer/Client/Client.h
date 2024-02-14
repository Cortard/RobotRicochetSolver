#ifndef RICOCHETSOCKETSSERVER_CLIENT_H
#define RICOCHETSOCKETSSERVER_CLIENT_H

#include <thread>
#include "../MultipleTypePointer/MultipleTypePointer.h"
#include "../Logs/Logs.h"
#include "../Socket/Socket.h"

class Client {
public:
    bool busy;

    Client();

    void startProcess(Socket* newSocket, unsigned int newId);
    void askStop();
    void waitStop();

    ~Client();

private:
    Socket* socket;
    unsigned int id;
    std::thread processThread;
    bool shouldStop;

    MultipleTypePointer output;

    void setUp(Socket* newSocket, unsigned int newId);
    void process();
    void processLoop();
};

#endif //RICOCHETSOCKETSSERVER_CLIENT_H
