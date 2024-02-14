#include <csignal>

#include "Logs/Logs.h"
#include "Server/Server.h"
#include "Socket/Socket.h"

void stopServer(int signum) {
    Logs::write("Received signal " + std::to_string(signum), LOG_LEVEL_INFO);
    Server::stop();
}

int main() {
    if(!Logs::write("Start Server",LOG_LEVEL_INFO)) return EXIT_FAILURE;
    signal(SIGTERM, stopServer);
    signal(SIGINT, stopServer);
    signal(SIGPIPE, stopServer);
    signal(SIGABRT, stopServer);

    if(Socket::init()==EXIT_FAILURE){
        Logs::write("Error while initializing socket",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }Logs::write("Socket initialized",LOG_LEVEL_INFO);

    Server::run();

    Socket::end();

    return 0;
}
