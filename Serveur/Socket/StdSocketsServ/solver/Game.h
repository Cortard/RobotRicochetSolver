#ifndef STDSOCKETSSERVER_GAME_H
#define STDSOCKETSSERVER_GAME_H

#include <iostream>
#include <cstring>

#define NORTH 0x01 // 0b00000001 1
#define EAST  0x02 // 0b00000010 2
#define SOUTH 0x04 // 0b00000100 4
#define WEST  0x08 // 0b00001000 8
#define ROBOT 0x10 // 0b00010000 16

class Game {
public:
    unsigned int moves[256]; //tableau des distances au goal moves[256]
    unsigned int grid[256]; //grille de jeu 16x16 grid[256]
    unsigned int* robots; //tableau de robots (le premiers celui qui doit atteindre le but) robots[4]
    int nbRobots; //nombre de robots
    bool coloredWalls; //tableau des murs colorés
    unsigned int token; //goal
    bool globalToken; //All robots can reach the goal
    unsigned int last; //dernier mouvement
    unsigned char* path; //chemin

    Game(int nbRobots, bool coloredWalls, bool globalGoal) : nbRobots(nbRobots), coloredWalls(coloredWalls), globalToken(globalGoal)
    {
        //memset(moves, 0xff, sizeof(moves)); useless because of the precompute_minimum_moves function
        memset(grid, 0, sizeof(grid));
        robots = new unsigned int[nbRobots];
        memset(robots, 0, sizeof(unsigned int) * nbRobots);
        token = 0;
        last = 0;
        path = nullptr;
    }

    void setNbRobots(int nbRobots) {
        this->nbRobots = nbRobots;
        delete[] robots;
        robots = new unsigned int[nbRobots];
        memset(robots, 0, sizeof(unsigned int) * nbRobots);
    }

    void prepareGrid() {
        //set borders
        for (int i = 0; i < 16; i++) grid[i]|= NORTH;
        for (int i = 240; i < 256; i++) grid[i]|= SOUTH;
        for (int i = 0; i < 256; i+=16) grid[i]|= WEST;
        for (int i = 15; i < 256; i+=16) grid[i]|= EAST;
        //119 120 135 136
        grid[118]|= EAST;
        grid[119]|= WEST|NORTH;
        grid[103]|= SOUTH;

        grid[121]|= WEST;
        grid[120]|= EAST|NORTH;
        grid[104]|= SOUTH;

        grid[134]|= EAST;
        grid[135]|= WEST|SOUTH;
        grid[151]|= NORTH;

        grid[137]|= WEST;
        grid[136]|= EAST|SOUTH;
        grid[152]|= NORTH;

        for (int i = 0; i < nbRobots; i++) {
            if (robots[i] < 0 || robots[i] > 255) {
                if(i==0) robots[i]=0;
                else robots[i] = 119 + (i-1)%2 + (i > 2 ? 16 : 0);
            }
        }
    }

    ~Game() {
        delete[] robots;
        delete[] path;
    }
};

#endif //STDSOCKETSSERVER_GAME_H
