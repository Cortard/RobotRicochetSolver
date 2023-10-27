#include "solver.h"

unsigned int Solver::search(Game *game,
                            unsigned char *path,
                            void (*callback)(unsigned int, unsigned int, unsigned int, unsigned int)) {
    if(game_over(game)) return 0;//si le jeu est fini

    unsigned int result = 0;
    Set *set = new Set();//initialise le set

    precompute_minimum_moves(game);//calcul des distances minimales

    for (unsigned int max_depth = 1; max_depth < MAX_DEPTH; max_depth++) {
        nodes = 0;//itialise les stats
        hits = 0;
        inner = 0;
        result = _search(game, 0, max_depth, path, set);//lance la recherche avec max_depth
    }

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

unsigned int Solver::_search(Game *game, unsigned int depth, unsigned int max_depth, unsigned char *path, Set *set) {
    nodes++;
    if(game_over(game)) return depth;//si le jeu est fini
    if (depth == max_depth) return 0;//si la profondeur max est atteinte
    unsigned int height = max_depth - depth;//hauteur de l'arbre
    if(game->moves[game->robots[0]] > height) return 0;//si le goal est trop loin

    // $prepare dans le set l
    //
}
