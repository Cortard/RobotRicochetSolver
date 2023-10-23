#ifndef BOARD_H
#define BOARD_H

#include <QMap>

#include "solver.h"

class Board {
private:
    int cases[256];
    QMap<unsigned int, int> objectives;
    QMap<unsigned int, int> robots;
    Solver solver;

    int translate(int x, int y);

public:
    Board();
    Board(int *cases, QMap<unsigned int, int> objectives, QMap<unsigned int, int> robots);

    bool load(int *cases, QMap<unsigned int, int> objectives, QMap<unsigned int, int> robots);

    void addWall(int x, int y, unsigned int dir);
    void removeWall(int x, int y, unsigned int dir);

    void addObjective(int x, int y, unsigned int id);
    void removeObjective(int x, int y, unsigned int id);

    void addRobot(int x, int y, unsigned int id);
    void removeRobot(int x, int y, unsigned int id);
    void moveRobot(unsigned int id, unsigned int dir);
};

#endif // BOARD_H
