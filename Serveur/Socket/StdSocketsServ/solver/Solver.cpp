#include <map>
#include <cstring>
#include "Solver.h"


int Solver::search(Game *game, unsigned char *path, bool (*callBack)(unsigned int, std::chrono::seconds), std::chrono::seconds* durationProcess, unsigned int* nbProcess, std::mutex* mutexTime) {
    auto startAll = std::chrono::high_resolution_clock::now();//début du chrono
    if(game_over(game)) return 0;//si le jeu est fini
    unsigned int result = 0;
    bool callBackResult = true;
    void *set;
    if(game->nbRobots<5)
        set= new std::map<unsigned int,unsigned int>();//initialise le set
    else
        set= new std::map<unsigned  long long,unsigned int>();//initialise le set

    precompute_minimum_moves(game);//calcul des distances minimales

    for (unsigned int max_depth = 1; max_depth < MAX_DEPTH; ++max_depth) {
        auto start = std::chrono::high_resolution_clock::now();//début du chrono
        if(game->nbRobots<5)//lance la recherche avec max_depth
            result = _search(game, 0, max_depth, path, static_cast<std::map<unsigned int, unsigned int>*>(set));
        else
            result = _search(game, 0, max_depth, path, static_cast<std::map<unsigned long long, unsigned int>*>(set));
        if(result==0) callBackResult=callBack(max_depth, std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start));//appel le callback
        if (result) {
            break;
        }else if(! callBackResult) break;
    }
    if(game->nbRobots<5) {
        std::destroy(((std::map<unsigned int, unsigned int> *) set)->begin(),((std::map<unsigned int, unsigned int> *) set)->end());
        delete static_cast<std::map<unsigned int, unsigned int>*>(set);
    }else{
        std::destroy(((std::map<unsigned long long, unsigned int> *) set)->begin(),((std::map<unsigned long long, unsigned int> *) set)->end());
        delete static_cast<std::map<unsigned long long, unsigned int>*>(set);
    }
    if(!callBackResult) return -1;
    if(result){
        std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - startAll;//fin du chrono
        mutexTime->lock();
        (*durationProcess)+=std::chrono::duration_cast<std::chrono::seconds>(elapsed);
        (*nbProcess)++;
        mutexTime->unlock();
    }
    return static_cast<int>(result);
}

bool Solver::game_over(Game *game) {
    //le robot goal est sur le goal
    return game->robots[0] == game->token;
}

void Solver::precompute_minimum_moves(Game *game) {
    bool statuts[256];//tableau a visiter ou non
    memset(statuts, 0, sizeof(statuts));//initialise le tableau de statuts à false
    memset(game->moves, 0xff, sizeof(game->moves));//initialise le tableau des moves à 'infini' 0xffffffff
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

template <typename setType>
unsigned int Solver::_search(Game *game, unsigned int depth, unsigned int max_depth, unsigned char *path, setType *set) {
    if(game_over(game)) return depth;//si le jeu est fini
    if (depth == max_depth) return 0;//si la profondeur max est atteinte
    unsigned int height = max_depth - depth;//hauteur de l'arbre
    if(game->moves[game->robots[0]] > height) return 0;//si le goal est trop loin
    bool fiveRobots = std::is_same<setType,std::map<unsigned long long, unsigned int>>::value;
    if(height!=1 && !set_add(set, make_key(game,fiveRobots), height,fiveRobots)) {//si le set contient la clé plus rapidement
        return 0;
    }
    for(unsigned int robot=0; robot<game->nbRobots; robot++){
        if(robot && game->moves[game->robots[0]] == height) continue;//si le robot n'est pas celui du goal et que le goal est à la bonne distance pour le principale
        for (unsigned int direction=1; direction<=8;direction<<=1){//toutes les direction
            if(!can_move(game, robot, direction)) continue;//si le robot ne peut pas bouger dans cette direction
            unsigned int undo = do_move(game, robot, direction);//on bouge le robot
            unsigned int result = _search(game, depth+1, max_depth, path, set);//on continue la recherche
            undo_move(game, undo);//on annule le mouvement
            if(result){//si le résultat est différent de 0
                path[depth] = PACK_MOVE(robot, direction);//on ajoute le mouvement au path
                return result;
            }
        }
    }
    return 0;
}

void Solver::swap(unsigned int *array, unsigned int a, unsigned int b) {
    unsigned int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

unsigned long long Solver::make_key(Game *game, bool fiveRobots) {
    unsigned int robots[4+fiveRobots];
    std::memcpy(robots, game->robots, (4+fiveRobots) * sizeof(unsigned int));
    if (robots[1] > robots[2]) {
        swap(robots, 1, 2);
    }
    if (robots[2] > robots[3]) {
        swap(robots, 2, 3);
    }
    if (robots[1] > robots[2]) {
        swap(robots, 1, 2);
    }
    if (!fiveRobots) return MAKE_KEY(robots);
    if (robots[3] > robots[4]) {
        swap(robots, 3, 4);
    }
    if (robots[2] > robots[3]) {
        swap(robots, 2, 3);
    }
    if (robots[1] > robots[2]) {
        swap(robots, 1, 2);
    }
    unsigned long long key = MAKE_KEY(robots);
    key |= static_cast<unsigned long long>(robots[4]) << 32;
    return key;
}

template <typename setType>
bool Solver::set_add(setType* set, unsigned long long key, unsigned int depth, bool moreThan4Robots){
    if (moreThan4Robots) {
        auto it = set->find(key);//on cherche la clé dans le set
        if(it == set->end()){//si la clé n'est pas dans le set
            set->insert(std::pair<unsigned long long ,unsigned int>(key, depth));//on l'ajoute
            return true;
        }
        if (it->second < depth){//si la nouvelle profondeur est supérieure
            it->second = depth;//on met à jour la profondeur
            return true;
        }
        return false;
    }
    auto it = set->find((unsigned int) key);//on cherche la clé dans le set
    if(it == set->end()){//si la clé n'est pas dans le set
        set->insert(std::pair<unsigned int,unsigned int>((unsigned int) key, depth));//on l'ajoute
        return true;
    }
    if (it->second < depth){//si la nouvelle profondeur est supérieure
        it->second = depth;//on met à jour la profondeur
        return true;
    }
    return false;
}

bool Solver::can_move(Game *game, unsigned int robot, unsigned int direction) {
    unsigned int index = game->robots[robot];//index de la case de départ
    if (HAS_WALL(game->grid[index], direction)) return false;//si il y a un mur dans la direction
    if (game->last == PACK_MOVE(robot, REVERSE[direction])) return false;//si le robot vient de cette direction
    index += OFFSET[direction];//on avance dans la direction
    if (HAS_ROBOT(game->grid[index])) return false;//si il y deja un robot sur la case
    return true;
}

unsigned int Solver::do_move(Game *game, unsigned int robot, unsigned int direction){
    unsigned int start = game->robots[robot];//case de départ
    unsigned int end = compute_move(game, robot, direction);//calcul case d'arrivée
    unsigned int last =game->last;//dernier mouvement
    game->robots[robot] = end;//on met à jour la position du robot
    game->last = PACK_MOVE(robot, direction);//on met à jour le dernier mouvement
    UNSET_ROBOT(game->grid[start]);//on enlève le robot de la case de départ
    SET_ROBOT(game->grid[end]);//on met le robot sur la case d'arrivée
    return PACK_UNDO(robot, start, last);//on retourne les modifications
}

void Solver::undo_move(Game *game, unsigned int undo){
    unsigned int robot = UNPACK_ROBOT(undo); //recupere le robot
    unsigned int start = UNPACK_START(undo); //recupere la case de départ du mouvement
    unsigned int last = UNPACK_LAST(undo); //recupere le dernier mouvement
    unsigned int end = game->robots[robot]; //recupere la case d'arrivée du mouvement
    game->robots[robot] = start; //on remet le robot sur la case de départ
    game->last = last; //on remet le dernier mouvement
    SET_ROBOT(game->grid[start]); //on remet le robot sur la case de départ
    UNSET_ROBOT(game->grid[end]); //on enlève le robot de la case d'arrivée
}

unsigned int Solver::compute_move(Game *game, unsigned int robot, unsigned int direction){
    unsigned int index = game->robots[robot]+OFFSET[direction];//première case parcourue
    while (true){
        if (HAS_WALL(game->grid[index], direction)) break;//si il y a un mur dans la direction
        unsigned int next = index + OFFSET[direction];//case suivante
        if (HAS_ROBOT(game->grid[next])) break;//si il y deja un robot sur la case
        index = next;//on avance dans la direction
    }
    return index;//on retourne la case d'arrivée
}