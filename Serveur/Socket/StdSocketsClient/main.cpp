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

#include <opencv2/opencv.hpp>

bool picture = true;

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

        cv::Mat mat=cv::imread("./picture/default.jpg", cv::IMREAD_COLOR);
        unsigned int pictureSize[2] = {static_cast<unsigned int>(mat.rows), static_cast<unsigned int>(mat.cols)};
        std::cout<<pictureSize[0]<<" "<<pictureSize[1]<<std::endl;
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

        char* matTemp= reinterpret_cast<char *>(mat.data);


        cv::Mat img = cv::Mat(static_cast<int>(pictureSize[0]), static_cast<int>(pictureSize[1]), CV_8UC3, (unsigned*)matTemp);
        cv::imwrite("./test.jpg", img);
        /*
        result = send(sockServ, matTemp, pictureSize[0] * pictureSize[1] * 3, 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer l'image\n");
            return EXIT_FAILURE;
        }printf("Image envoyé\n");
         */

        std::cout<<pictureSize[0]<<" "<<pictureSize[1]<<std::endl;
        for(int i=0;i<pictureSize[0]*pictureSize[1]*3 ;++i) {
            int res=send(sockServ, matTemp+i, 1, 0);
            if (res == SOCKET_ERROR) {
                printf("Impossible d'envoyer l'image\n");
                return EXIT_FAILURE;
            }
        }printf("Image envoyé\n");

        char confirm;
        result = recv(sockServ, (char *) &confirm, sizeof(confirm), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible de recevoir la confirmation de l'image\n");
            return EXIT_FAILURE;
        }printf("Confirmation de l'image reçu\n");

        if (confirm != 1) {
            printf("Confirmation de l'image pas ok\n");
            return EXIT_FAILURE;
        }printf("Confirmation de l'image ok\n");

        int nbRobots=4;
        result = send(sockServ, &nbRobots, sizeof(nbRobots), 0);
        if(result == SOCKET_ERROR){
            printf("Impossible d'envoyer le nombre de robots\n");
            return EXIT_FAILURE;
        }printf("Nombre de robots envoyé\n");

        int  nbRobotsReceive;
        result = recv(sockServ, &nbRobotsReceive, sizeof(nbRobots), 0);
        if(result == SOCKET_ERROR){
            printf("Impossible de recevoir le nombre de robots\n");
            return EXIT_FAILURE;
        }printf("Nombre de robots reçu\n");

        if(nbRobotsReceive!=nbRobots){
            printf("Nombre de robots reçu différent de celui envoyé\n");
            return EXIT_FAILURE;
        }printf("Nombre de robots reçu identique à celui envoyé\n");

        unsigned int robots[4]={176, 145, 211, 238};
        result = send(sockServ, (char *) &robots, sizeof(robots), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer les robots\n");
            return EXIT_FAILURE;
        }printf("Robots envoyé\n");

        unsigned int token=54;
        result = send(sockServ, (char *) &token, sizeof(token), 0);
        if (result == SOCKET_ERROR) {
            printf("Impossible d'envoyer le goal\n");
            return EXIT_FAILURE;
        }printf("Goal envoyé\n");

    }else{//grille*******************************************************************************************************
        char typeDate = 2;
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
        //gripType|=2;
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
        //unsigned int robots[5]={176, 145, 211, 238,120};
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

    }

    int time;
    int result = recv(sockServ, (char *) &time, sizeof(time), MSG_WAITALL);
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

    char confirm=0;
    result = send(sockServ, &confirm, sizeof(char), 0);
    if (result == SOCKET_ERROR) {
        printf("Impossible d'envoyer confirmation\n");
        return EXIT_FAILURE;
    }printf("Confirmation envoyée\n");

    for(unsigned char& i : path){
        printf("%d, ", i);
    }printf("\n");
    printf("1, 2, 4, 17, 18, 40, 33, 8, 1, 2, 1, 2, 56, 49, 56, 49, 50, 49, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \n");



#if defined (WIN32)
    WSACleanup();
#endif
    return 0;
}
