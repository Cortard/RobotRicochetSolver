#ifndef RICOCHETSOCKETSSERVER_CLIENT_H
#define RICOCHETSOCKETSSERVER_CLIENT_H

#include <thread>
#include "../socket.h"
#include "../Logs/Logs.h"

class Client {
public:
    Client(SOCKET &socket, unsigned int id);

    void startProcess();
    void askStop();
    void waitStop();

    ~Client();

private:
    SOCKET socket;
    unsigned int id;
    std::thread processThread;
    bool shouldStop;

    void processLoop() const { //TODO: implement
        int i=0;
        while (!shouldStop && i<5) {
            sleep(1);
            ++i;
        }
        if(shouldStop) Logs::write("Client process stopped id: "+std::to_string(id),LOG_LEVEL_WARNING);
    }
};

#endif //RICOCHETSOCKETSSERVER_CLIENT_H
