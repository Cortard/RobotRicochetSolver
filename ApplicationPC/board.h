#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <QPointF>
#include <observer.h>

class Board : public Observable{
public:
    Board();

    static int getBoardSize();
    int getIndex(int x, int y) const;

    void moveObject(int id, int pos);

    void addWall(int x, int y, char dir);
    void addObjective(int id, int pos);

    // premier int : id , deuxieme int : position du tableau
    std::map<int, int> objectives;

private:
    static const int BOARD_SIZE = 16;
    int cases[256];

    std::map<int, int> robots;
};

#endif // BOARD_H
