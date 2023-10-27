#ifndef TRADUCTIONCPP_SOLVER_H
#define TRADUCTIONCPP_SOLVER_H

#include <iostream>
#include "Game.h"

#define MAX_DEPTH 20

#define NORTH 0x01 // 0b00000001
#define EAST  0x02 // 0b00000010
#define SOUTH 0x04 // 0b00000100
#define WEST  0x08 // 0b00001000
#define ROBOT 0x10 // 0b00010000

#define HAS_WALL(x, wall) (x & wall) // x & wall = 1 si x contient wall (et bit à bit)
#define HAS_ROBOT(x) (x & ROBOT) // x & ROBOT = 1 si x contient ROBOT (0b0001 0000) (et bit à bit)
#define SET_ROBOT(x) (x |= ROBOT) // -> x = x | ROBOT -> x = x | 0b0001 0000 ( x= ou bit à bit)
#define UNSET_ROBOT(x) (x &= ~ROBOT) // -> x = x & ~ROBOT -> x = x & 0b1110 1111 ( x= et non bit à bit)

#define PACK_MOVE(robot, direction) (robot << 4 | direction) // -> 0b00[00][0000] [bit de robot (0-3)] [bit de direction]
#define PACK_UNDO(robot, start, last) (robot << 16 | start << 8 | last) // -> 0b00[00][0000 0000][0000 0000] [bit de robot (0-3)] [bit de la case (0-255)] [bit de last (0-255)]
#define UNPACK_ROBOT(undo) ((undo >> 16) & 0xff) // 0b[0000 0000]a [0000 0000]b [0000 0000]c -> 0b[0000 0000]a (recupere bit de robot)
#define UNPACK_START(undo) ((undo >> 8) & 0xff) // 0b[0000 0000]a [0000 0000]b [0000 0000]c -> 0b[0000 0000]b (recupere bit de la case)
#define UNPACK_LAST(undo) (undo & 0xff) // 0b[0000 0000]a [0000 0000]b [0000 0000]c -> 0b[0000 0000]c (recupere bit de last)
#define MAKE_KEY(x) (x[0] | (x[1] << 8) | (x[2] << 16) | (x[3] << 24)) // -> 0b[0000 0000] [0000 0000] [0000 0000] [0000 0000] [robot 0 (goal)] [robot 1] [robot 2] [robot 3]

const unsigned int REVERSE[] = { //Inverse les directions
        //          N           E               S                               W
        0, SOUTH, WEST, 0, NORTH, 0, 0, 0, EAST
};

const int OFFSET[] = { //Décalage pour aller dans une direction
        //          N       E              S                            W
        0, -16, 1, 0, 16, 0, 0, 0, -1
};

class Solver {
public:
    Solver(){nodes=0; hits=0; inner=0;};
    unsigned int search(Game* game, unsigned char *path);
private:
    static bool game_over(Game *game);
    static void precompute_minimum_moves(Game *game);

    //hasmap
    static void swap(unsigned int *array, unsigned int a, unsigned int b);
    static unsigned int make_key(Game *game);
    static bool set_add(std::map<int,int>* set, unsigned int key, unsigned int depth);

    //move
    static bool can_move(Game *game, unsigned int robot, unsigned int direction);
    static unsigned int do_move(Game *game, unsigned int robot, unsigned int direction);
    static void undo_move(Game *game, unsigned int undo);
    static unsigned int compute_move(Game *game, unsigned int robot, unsigned int direction);

    unsigned int nodes, hits, inner;
    unsigned int _search(Game *game, unsigned int depth, unsigned int max_depth, unsigned char *path, std::map<int, int>* set);
    void callback(unsigned int max_depth, unsigned int nodes, unsigned int inner, unsigned int hits);
};

#endif //TRADUCTIONCPP_SOLVER_H
