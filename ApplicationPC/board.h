#ifndef BOARD_H
#define BOARD_H

// Directions possibles pour les murs
#define NORTH 0x01
#define EAST 0x02
#define SOUTH 0x04
#define WEST 0x08

// Vérifier si un mur est présent, le définir ou le supprimer
#define HAS_WALL(x,wall)(x & wall)
#define SET_WALL(x,wall)(x |= wall)
#define DEL_WALL(x,wall)(x &= ~wall)

// Récupérer la direction et l'id du robot
#define GET_DIRECTION(x) (x&0x0f)
#define GET_ROBOT(x) ((x>>4)&0x0f)

#include <map>
#include <QPointF>
#include <observer.h>

class Board : public Observable{
public:
    Board();

    #include "construct.h"

    static int getBoardSize();
    int getIndex(int x, int y) const;

    void moveObject(int id, int pos);
    void moveRobot(int id, int pos);

    void addWall(int x, int y, char dir);
    void addObjective(int id, int pos);
    void addRobot(int id, int pos);

    void removeWall(int pos);
    void removeRobot(int pos);
    void removeObj(int pos);

    // premier int : id , (deuxieme) int : position du tableau
    std::map<int, int> objectives;
    std::map<int, int> robots_move;
    std::map<int, int> robots_initial;
    unsigned int cases[256];

    // Variables pour le suivi du mouvement et de l'objectif actuel
    int mouvement=0;
    int objJeu=-1;

    int victoireHistoire=1;

    // Tableau pour stocker la solution
    unsigned char path[32];

    void reset();

private:
    static const int BOARD_SIZE = 16;
};

#endif // BOARD_H
