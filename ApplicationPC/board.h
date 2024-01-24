#ifndef BOARD_H
#define BOARD_H

#define NORTH 0x01
#define EAST 0x02
#define SOUTH 0x04
#define WEST 0x08

#define HAS_WALL(x,wall)(x & wall)
#define SET_WALL(x,wall)(x |= wall)
#define DEL_WALL(x,wall)(x &= ~wall)

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

    // premier int : id , deuxieme int : position du tableau
    std::map<int, int> objectives;
    std::map<int, int> robots;
    std::map<int, int> robots2;
    unsigned int cases[256];
    int mouvement=0;
    int objJeu=-1;


    //gridData = new int[]{9, 1, 5, 1, 3, 9, 1, 1, 1, 3, 9, 1, 1, 1, 1, 3, 8, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 3, 8, 0, 0, 0, 0, 2, 12, 0, 2, 9, 0, 0, 0, 0, 4, 2, 12, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 10, 9, 0, 0, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 6, 8, 0, 0, 0, 0, 4, 4, 0, 0, 2, 12, 0, 0, 2, 8, 1, 0, 0, 0, 0, 2, 9, 3, 8, 0, 0, 1, 0, 0, 2, 8, 0, 4, 0, 2, 12, 2, 12, 6, 8, 0, 0, 0, 0, 0, 6, 8, 18, 9, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 4, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 2, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 0, 0, 2, 9, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 2, 12, 2, 8, 0, 0, 16, 3, 8, 0, 0, 0, 4, 0, 0, 0, 0, 1, 2, 8, 6, 8, 0, 0, 0, 0, 0, 0, 3, 8, 0, 0, 0, 16, 2, 12, 5, 4, 4, 4, 6, 12, 4, 4, 4, 4, 6, 12, 4, 4, 6};
    //initialRobotPositions = new int[]{176, 145, 211, 238};

     unsigned char path[32] = {1, 2, 4, 17, 18, 40, 33, 8, 1, 2, 1, 2, 56, 49, 56, 49, 50, 49, 8, 4, 63};

    //unsigned char path[32];

    void reset();
    void resetPos(int postion);

private:
    static const int BOARD_SIZE = 16;
};

#endif // BOARD_H
