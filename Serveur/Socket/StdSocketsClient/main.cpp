#include <iostream>

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

#define IP "195.201.205.241"//195.201.205.241 127.0.0.1
#define PORT 9090

int main() {
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif

    if(erreur) return -1;

    SOCKET sockServ;
    sockServ = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sockAddrInter;
    sockAddrInter.sin_addr.s_addr = inet_addr(IP);//htonl(INADDR_ANY)
    sockAddrInter.sin_family = AF_INET;
    sockAddrInter.sin_port = htons(PORT);

    if(connect(sockServ, (SOCKADDR*)&sockAddrInter, sizeof (sockAddrInter))!= SOCKET_ERROR) {
        printf("Connexion à %s sur le port %d\n", inet_ntoa(sockAddrInter.sin_addr), htons(sockAddrInter.sin_port));
        size_t size=sizeof(size_t);
        char buffer[size];
        if(recv(sockServ, buffer, (int)size, 0) != SOCKET_ERROR) {
            printf("Recu taille\n");
            size_t msgSize = *(size_t*)buffer;
            char msg[msgSize];
            if(recv(sockServ, msg, (int)msgSize, 0) != SOCKET_ERROR) {
                printf("Recu message\n");
                printf("Message recu : %s\n", msg);
                shutdown(sockServ, 2);
            }
            else {
                printf("Erreur de reception message\n");
            }
        }
        else {
            printf("Erreur de reception taille\n");
        }
    } else {
        printf("Impossible de se connecter\n");
    }


    /* On ferme la socket précédemment ouverte */
    //closesocket(sockServ);


    #if defined (WIN32)
        WSACleanup();
    #endif

    return 0;
}
