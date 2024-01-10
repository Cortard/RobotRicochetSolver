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
#include "configue.h"

bool picture = false;

int main() {
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
        printf("Impossible de se connecter\n");
        return EXIT_FAILURE;
    }
    printf("Connecté a %s:%d\n", inet_ntoa(sockAddrInter.sin_addr), htons(sockAddrInter.sin_port));

    if(picture) {
        char typeDate = 0;
        int result = send(sockServ, (char *) &typeDate, sizeof(typeDate), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer le type de donnée\n");
            return EXIT_FAILURE;
        }printf("Type de donnée envoyé\n");

        char typeDateReceive;
        result = recv(sockServ, &typeDateReceive, sizeof(typeDate), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible de recevoir le type de donnée\n");
            return EXIT_FAILURE;
        }printf("Type de donnée reçu\n");

        if (typeDateReceive != typeDate) {
            printf("Type de donnée reçu différent de celui envoyé\n");
            return EXIT_FAILURE;
        }printf("Type de donnée reçu identique à celui envoyé\n");

        unsigned int pictureSize[2] = {10, 10};
        result = send(sockServ, (char *) &pictureSize, sizeof(pictureSize), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer la taille de l'image\n");
            return EXIT_FAILURE;
        }printf("Taille de l'image envoyé\n");

        unsigned long pictureSizeReceive;
        result = recv(sockServ, (char *) (&pictureSizeReceive), sizeof(pictureSize), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible de recevoir la taille de l'image\n");
            return EXIT_FAILURE;
        }printf("Taille de l'image reçu\n");

        if (pictureSizeReceive != pictureSize[0] * pictureSize[1] * 3) {
            printf("Taille de l'image reçu différent de celui envoyé\n");
            return EXIT_FAILURE;
        }printf("Taille de l'image reçu identique à celui envoyé\n");

        unsigned char picture[pictureSize[0] * pictureSize[1] * 3];
        for (int i = 0; i < pictureSize[0] * pictureSize[1] * 3; i++) {
            picture[i] = i % 255;
        }
        result = send(sockServ, (char *) &picture, sizeof(picture), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer l'image\n");
            return EXIT_FAILURE;
        }printf("Image envoyé\n");

        unsigned char confirm;
        result = recv(sockServ, (char *) &confirm, sizeof(confirm), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible de recevoir la confirmation de l'image\n");
            return EXIT_FAILURE;
        }printf("Confirmation de l'image reçu\n");

        if (confirm != 0) {
            printf("Confirmation de l'image pas ok\n");
            return EXIT_FAILURE;
        }printf("Confirmation de l'image ok\n");
    }else{//grille*******************************************************************************************************
        char typeDate = 1;
        int result = send(sockServ, (char *) &typeDate, sizeof(typeDate), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer le type de donnée\n");
            return EXIT_FAILURE;
        }printf("Type de donnée envoyé\n");

        char typeDateReceive;
        result = recv(sockServ, &typeDateReceive, sizeof(typeDate), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible de recevoir le type de donnée\n");
            return EXIT_FAILURE;
        }printf("Type de donnée reçu\n");

        if (typeDateReceive != typeDate) {
            printf("Type de donnée reçu différent de celui envoyé\n");
            return EXIT_FAILURE;
        }printf("Type de donnée reçu identique à celui envoyé\n");

        char gripType = 0;
        result = send(sockServ, (char *) &gripType, sizeof(gripType), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer le type de grille\n");
            return EXIT_FAILURE;
        }printf("Type de grille envoyé\n");

        char gripTypeReceive;
        result = recv(sockServ, (char *) &gripTypeReceive, sizeof(gripType), MSG_WAITALL);
        if (result == SOCKET_ERROR) {
            printf("Impossible de recevoir le type de grille\n");
            return EXIT_FAILURE;
        }printf("Type de grille reçu\n");

        if (gripTypeReceive != gripType) {
            printf("Type de grille reçu différent de celui envoyé\n");
            return EXIT_FAILURE;
        }printf("Type de grille reçu identique à celui envoyé\n");

        unsigned int grid[256]={9, 1, 5, 1, 3, 9, 1, 1, 1, 3, 9, 1, 1, 1, 1, 3, 8, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 3, 8, 0, 0, 0, 0, 2, 12, 0, 2, 9, 0, 0, 0, 0, 4, 2, 12, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 10, 9, 0, 0, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 6, 8, 0, 0, 0, 0, 4, 4, 0, 0, 2, 12, 0, 0, 2, 8, 1, 0, 0, 0, 0, 2, 9, 3, 8, 0, 0, 1, 0, 0, 2, 8, 0, 4, 0, 2, 12, 2, 12, 6, 8, 0, 0, 0, 0, 0, 6, 8, 18, 9, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 4, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 2, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 0, 0, 2, 9, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 2, 12, 2, 8, 0, 0, 16, 3, 8, 0, 0, 0, 4, 0, 0, 0, 0, 1, 2, 8, 6, 8, 0, 0, 0, 0, 0, 0, 3, 8, 0, 0, 0, 16, 2, 12, 5, 4, 4, 4, 6, 12, 4, 4, 4, 4, 6, 12, 4, 4, 6};
        unsigned int robots[4]={176, 145, 211, 238};
        //unsigned int robots[4]={55, 145, 211, 238};
        unsigned int token=54;
        result = send(sockServ, (char *) &grid, sizeof(grid), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer la grille\n");
            return EXIT_FAILURE;
        }printf("Grille envoyé\n");

        result = send(sockServ, (char *) &robots, sizeof(robots), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer les robots\n");
            return EXIT_FAILURE;
        }printf("Robots envoyé\n");
        result = send(sockServ, (char *) &token, sizeof(token), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer le goal\n");
            return EXIT_FAILURE;
        }printf("Goal envoyé\n");

        int time;
        result = recv(sockServ, (char *) &time, sizeof(time), MSG_WAITALL);
        if (result == SOCKET_ERROR) {
            printf("Impossible de recevoir le temps\n");
            return EXIT_FAILURE;
        }printf("Temps reçu : %d\n", time);

        char flag=1;
        do{
            result = SOCKET_ERROR;
            while(result==SOCKET_ERROR)
                result = recv(sockServ, (char *) &flag, sizeof(flag), MSG_WAITALL);
            printf("Flag reçu : %d\n", flag);
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
                printf("Impossible de recevoir le state\n");
                return EXIT_FAILURE;
            }
            printf("depth : %d, time in seconds : %d\n", state[0], state[1]);
        } while (flag==1);

        switch(flag){
            case 2 :
                printf("Pas de solution\n");
                return EXIT_FAILURE;
            case 3 :
                printf("Solution trouvé\n");
                break;
            default:
                printf("Flag inconnu\n");
                return EXIT_FAILURE;
        }

        unsigned char path[32];
        result = recv(sockServ, (char *)&path, sizeof(path), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible de recevoir le path\n");
            return EXIT_FAILURE;
        }printf("Path reçu\n");

        result = send(sockServ, (char *) &robots, sizeof(robots), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer confirmation\n");
            return EXIT_FAILURE;
        }printf("Confirmation envoyée\n");

        for(unsigned char& i : path){
            printf("%d, ", i);
        }

    }


#if defined (WIN32)
    WSACleanup();
#endif
    return 0;
}
