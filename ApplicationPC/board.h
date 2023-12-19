#ifndef BOARD_H
#define BOARD_H

#define NORTH 0x01
#define EAST 0x02
#define SOUTH 0x04
#define WEST 0x08

#define HAS_WALL(x,wall)(x & wall)
#define SET_WALL(x,wall)(x |= wall)
#define DEL_WALL(x,wall)(x &= ~wall)

#include <map>
#include <QPointF>
#include <observer.h>

class Board : public Observable{
public:
    Board();

    static int getBoardSize();
    int getIndex(int x, int y) const;

    void moveObject(int id, int pos);
    void moveRobot(int id, int pos);

    void addWall(int x, int y, char dir);
    void addObjective(int id, int pos);
    void addRobot(int id, int pos);

    void removeRobot(int pos);
    void removeObj(int pos);

    // premier int : id , deuxieme int : position du tableau
    std::map<int, int> objectives;
    std::map<int, int> robots;
    int cases[256];
    int mouvement=0;
    int objJeu=-1;

private:
    static const int BOARD_SIZE = 16;
};

#endif // BOARD_H
