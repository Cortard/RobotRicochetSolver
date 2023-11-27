#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <QPointF>

class Board {
public:
    Board();

    void addWall(int x, int y, char dir);
    void addObjective(int x, int y, int id);

    static int getBoardSize();
    int getIndex(int x, int y) const;
    void moveShape(QPointF);


private:
    static const int BOARD_SIZE = 16;
    int cases[256];
    std::map<int, int> objectives;
    std::map<int, int> robots;
};

#endif // BOARD_H
