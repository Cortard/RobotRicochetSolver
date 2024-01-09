#ifndef STDSOCKETSSERVER_GAME_H
#define STDSOCKETSSERVER_GAME_H

#include <iostream>

class Game {
public:
    unsigned int moves[256]; //tableau des distances au goal moves[256]
    unsigned int grid[256]; //grille de jeu 16x16 grid[256]
    unsigned int robots[4]; //tableau de robots (le premiers celui qui doit atteindre le but) robots[4]
    unsigned int token; //goal
    unsigned int last; //dernier mouvement

    Game() {
        //memset(moves, 0xff, sizeof(moves)); useless because of the precompute_minimum_moves function
        memset(grid, 0, sizeof(grid));
        memset(robots, 0, sizeof(robots));
        token = 0;
        last = 0;
    }
};

#endif //STDSOCKETSSERVER_GAME_H
