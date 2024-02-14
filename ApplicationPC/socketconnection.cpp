#include "socketconnection.h"

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close (s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <iostream>
#include "configure.h"

int SocketConnection::getSolution(Board* board) {
    #if defined (WIN32)
        WSADATA WSAData;
        int _erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
        if(_erreur) return -1;
    #endif

    SOCKET sockServ;
    sockServ = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sockAddrInter;
    sockAddrInter.sin_addr.s_addr = inet_addr(IP);//htonl(INADDR_ANY)
    sockAddrInter.sin_family = AF_INET;
    sockAddrInter.sin_port = htons(PORT);

    if(connect(sockServ, (SOCKADDR*)&sockAddrInter, sizeof (sockAddrInter))== SOCKET_ERROR) {
        std::cout << "Impossible de se connecter" << std::endl;;
        return EXIT_FAILURE;
    }
    std::cout << "Connecte a " << inet_ntoa(sockAddrInter.sin_addr) << ":" << htons(sockAddrInter.sin_port) << std::endl;

    char typeDate = 2;
    int result = send(sockServ, (char *) &typeDate, sizeof(typeDate), 0);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible d envoyer le type de donnee" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Type de donnee envoye" << std::endl;

    char typeDateReceive;
    result = recv(sockServ, &typeDateReceive, sizeof(typeDate), 0);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible de recevoir le type de donnee" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Type de donnee recu" << std::endl;

    if (typeDateReceive != typeDate) {
        std::cout << "Type de donnee recu différent de celui envoye" << std::endl;
            return EXIT_FAILURE;
    }std::cout << "Type de donnee recu identique a celui envoye" << std::endl;

    char gripType = 0;
    result = send(sockServ, (char *) &gripType, sizeof(gripType), 0);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible d envoyer le type de grille" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Type de grille envoye" << std::endl;

    char gripTypeReceive;
    result = recv(sockServ, (char *) &gripTypeReceive, sizeof(gripType), MSG_WAITALL);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible de recevoir le type de grille" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Type de grille recu" << std::endl;

    if (gripTypeReceive != gripType) {
        std::cout << "Type de grille recu different de celui envoye" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Type de grille recu identique a celui envoye" << std::endl;

    unsigned int grid[256];
    for(int i=0; i<256; ++i) {
        grid[i] = board->cases[i];
    }
    unsigned int robots[4];
    std::map<int, int>::iterator it;
    int cpt = 1;
    for(it = board->robots_move.begin(); it != board->robots_move.end(); ++it) {
        if(board->objJeu / 4 == it->first) {
            robots[0] = it->second;
            grid[it->second] |= 0x10;
            continue;
        }
        robots[cpt] = it->second;
        grid[it->second] |= 0x10;
        ++cpt;

    }
    grid[0] = 9;
    for(int i=0; i<256; ++i) {
        if(i % 16 == 0)
            std::cout << std::endl;
        std::cout << grid[i] << " ";
    }
    unsigned int token=(unsigned int) (board->objectives.at(board->objJeu));
    result = send(sockServ, (char *) &grid, sizeof(grid), 0);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible d envoyer la grille" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Grille envoye" << std::endl;

    result = send(sockServ, (char *) &robots, sizeof(robots), 0);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible d envoyer les robots" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Robots envoye" << std::endl;
    result = send(sockServ, (char *) &token, sizeof(token), 0);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible d envoyer le goal" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Goal envoye" << std::endl;

    int time;
    result = recv(sockServ, (char *) &time, sizeof(time), MSG_WAITALL);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible de recevoir le temps" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Temps recu : " << time << std::endl;

    char flag=1;
    do{
        result = SOCKET_ERROR;
        while(result==SOCKET_ERROR)
        result = recv(sockServ, (char *) &flag, sizeof(flag), MSG_WAITALL);
        std::cout << "Flag recu : " << (int)flag << std::endl;
        if(flag!=1) break;
        /*
        result = send(sockServ, (char *) &flag, sizeof(flag), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer la confirmation flag\n");
        return EXIT_FAILURE;
        }
        */
        int state[2];
        result = recv(sockServ, (char *) &state, sizeof(state), MSG_WAITALL);
        if (result == SOCKET_ERROR) {
            std::cout << "Impossible de recevoir le state" << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "depth : " << state[0] << " time in seconds : " << state[1] << std::endl;
    } while (flag==1);
    switch(flag){
        case 2 :
        std::cout << "Pas de solution" << std::endl;
            return EXIT_FAILURE;
        case 3 :
            std::cout << "Solution trouve" << std::endl;
            break;
        default:
            std::cout << "Flag inconnu" << std::endl;
            return EXIT_FAILURE;
    }

    unsigned char path[32];
    result = recv(sockServ, (char *)&path, sizeof(path), 0);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible de recevoir le path" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Path recu" << std::endl;

    result = send(sockServ, (char *) &robots, sizeof(robots), 0);
    if (result == SOCKET_ERROR) {
        std::cout << "Impossible d envoyer confirmation" << std::endl;
        return EXIT_FAILURE;
    }std::cout << "Confirmation envoyee" << std::endl;

    for(int i=0;i<32;i++){
        board->path[i]=path[i];
    }

    for(unsigned char& i : path){
        std::cout << (int)i << ", ";
    }
    std::cout << std::endl;

    #if defined (WIN32)
        WSACleanup();
    #endif

    return 0;
}
