#ifndef STDSOCKETSSERVER_GAME_H
#define STDSOCKETSSERVER_GAME_H

#include <iostream>
#include <cstring>

class Game {
public:
    unsigned int moves[256]; //tableau des distances au goal moves[256]
    unsigned int grid[256]; //grille de jeu 16x16 grid[256]
    unsigned int* robots; //tableau de robots (le premiers celui qui doit atteindre le but) robots[4]
    int nbRobots; //nombre de robots
    bool coloredWalls; //tableau des murs colorés
    unsigned int token; //goal
    unsigned int last; //dernier mouvement

    Game(int nbRobots, bool coloredWalls) : nbRobots(nbRobots), coloredWalls(coloredWalls) {
        //memset(moves, 0xff, sizeof(moves)); useless because of the precompute_minimum_moves function
        memset(grid, 0, sizeof(grid));
        robots = new unsigned int[nbRobots];
        memset(robots, 0, sizeof(unsigned int) * nbRobots);
        token = 0;
        last = 0;
    }

    void setNbRobots(int nbRobots) {
        this->nbRobots = nbRobots;
        delete[] robots;
        robots = new unsigned int[nbRobots];
        memset(robots, 0, sizeof(unsigned int) * nbRobots);
    }

    ~Game() {
        delete[] robots;
    }
};

#endif //STDSOCKETSSERVER_GAME_H
