#include "solver.h"

unsigned int Solver::search(Game *game,
                            unsigned char *path,
                            void (*callback)(unsigned int, unsigned int, unsigned int, unsigned int)) {
    if(game_over(game)) return 0;

    unsigned int result = 0;
    Set *set = new Set();

    precompute_minimum_moves(game);


    return 0;
}

bool Solver::game_over(Game *game) {
    //le robot goal est sur le goal
    return game->robots[0] == game->token;
}

void Solver::precompute_minimum_moves(Game *game) {
    bool statuts[256];//tableau a visiter ou non
    for(unsigned int i = 0; i < 256; i++) {
        statuts[i] = false;//initialise le tableau de statuts à false
        game->moves[i] = 0xffffffff;//initialise le tableau des moves à 'infini' 0xffffffff
    }
    game->moves[game->token] = 0;//le goal est à une distance de 0
    statuts[game->token] = true;//le goal est visité

    bool done = false;
    while (!done){//parcours en profondeur de la grille
        done= true;
        for (unsigned int i=0; i<256; i++){
            if(!statuts[i]) continue; //si la case n'est pas a visiter, on passe à la suivante

            statuts[i] = false; //la case n'est plus à visiter puisqu'on le fait
            unsigned int depth = game->moves[i] + 1;//la profondeur augmente de 1 par rapport à la case précédente
            for (unsigned int direction = 1; direction <= 8; direction <<= 1) {//pour chaque direction

                unsigned int index = i; //index de la case de départ
                while (!HAS_WALL(game->grid[index], direction)) { //tant qu'il n'y a pas de mur
                    index += OFFSET[direction]; //on avance dans la direction

                    if (game->moves[index] > depth) { //si l'ancienne profondeur est supérieure à la nouvelle
                        game->moves[index] = depth;  //on met à jour la profondeur
                        statuts[index] = true; //la distance est mise à jour donc on doit la revisiter
                        done = false; //on continue la recherche
                    }
                }
            }
        }
    }
}
