#ifndef BOARD_H
#define BOARD_H

#define NORTH 0x01
#define EAST  0x02
#define SOUTH 0x04
#define WEST  0x08

#define HAS_WALL(x, wall) (x & wall)
#define ADD_WALL(x, wall) (x |= wall)

#include <map>

class Board {
public:
    int cases[256];
    int objectives[17];
    std::map<int, int> robots;

    Board() {
        for (int & i : cases) { i = 0; }
        for (int & objective : objectives) { objective = -1; }
    }
};

#endif //BOARD_H