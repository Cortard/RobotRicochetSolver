#ifndef TRADUCTIONCPP_GAME_H
#define TRADUCTIONCPP_GAME_H

struct Game {
public:
    unsigned int moves[256]; //tableau des distances au goal
    unsigned int grid[256]; //grille de jeu 16x16
    unsigned int robots[4]; //tableau de robots (le premiers celui qui doit atteindre le but)
    unsigned int token; //goal
    unsigned int last; //dernier mouvement
};

#endif //TRADUCTIONCPP_GAME_H
