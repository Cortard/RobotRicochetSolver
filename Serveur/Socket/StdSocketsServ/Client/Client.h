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
        while (!shouldStop) {
            sleep(1);
        }
        Logs::write("Client process stopped id: "+std::to_string(id),LOG_LEVEL_DEBUG);
    }
};

#endif //RICOCHETSOCKETSSERVER_CLIENT_H
