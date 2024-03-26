#include "board.h"
#include <iostream>
#include "observer.h"

Board::Board() {
    memset(cases, 0, sizeof(int)*256); // Set each case with no wall by default

    for(int i=0;i<17;i++){ // Fill objectives list by default
        this->objectives.insert(std::pair<int,int>(i,-1));
    }

    for(int i=0;i<5;i++){ // Fill robots related arrays by default
        this->robots_move.insert(std::pair<int,int>(i,-1));
        this->robots_initial.insert(std::pair<int,int>(i,-1));
    }

    for(int i=0;i<16;i++){ // Add center walls
        SET_WALL(cases[i], NORTH);
        SET_WALL(cases[i+16*15], SOUTH);
        SET_WALL(cases[i*16], WEST);
        SET_WALL(cases[i*16+15], EAST);
    }

    // Add outer walls
    SET_WALL(cases[151],NORTH);
    SET_WALL(cases[152],NORTH);
    SET_WALL(cases[103],SOUTH);
    SET_WALL(cases[104],SOUTH);
    SET_WALL(cases[118],EAST);
    SET_WALL(cases[134],EAST);
    SET_WALL(cases[121],WEST);
    SET_WALL(cases[137],WEST);
}

int Board::getIndex(int x, int y) const {
    return (static_cast<int>(x / 25) + static_cast<int>(y / 25) * 16);
}

void Board::addObjective(int id, int pos) {
    this->objectives.at(id)=pos;
    notifyObserver();
}

void Board::removeObj(int pos) {
    std::map<int, int>::iterator it;
    for(it = this->objectives.begin(); it != this->objectives.end(); it++) {
        if (it->second == pos)
            (*it).second = -1;
    }

    // std::for_each(this->objectives.begin(), this->objectives.end(),
    //               [pos](auto& pair) {
    //     if (pair.second == pos) {
    //         pair.second = -1;
    //     }
    // });
    notifyObserver();
}

void Board::addRobot(int id, int pos) {
    this->robots_move.at(id)=pos;
    notifyObserver();
}

void Board::removeRobot(int pos) {
    std::map<int, int>::iterator it;
    for(it = robots_move.begin(); it != this->robots_move.end(); it++) {
        if (it->second == pos)
            (*it).second = -1;
    }

    // std::for_each(this->robots_move.begin(), this->robots_move.end(),
    //               [pos](auto& pair) {
    //     if (pair.second == pos) {
    //         pair.second = -1;
    //     }
    // });
    notifyObserver();
}

void Board::addWall(int x, int y, char dir) {
    int cellIndex = getIndex(x, y);
    switch (dir) {
    case 'N':
        if(HAS_WALL(cases[cellIndex], NORTH)==0){
            SET_WALL(cases[cellIndex], NORTH);
            SET_WALL(cases[cellIndex-16], SOUTH);
        }else{
            DEL_WALL(cases[cellIndex], NORTH);
            DEL_WALL(cases[cellIndex-16], SOUTH);
        }
        break;
    case 'E':
        if(HAS_WALL(cases[cellIndex], EAST)==0){
            SET_WALL(cases[cellIndex], EAST);
            SET_WALL(cases[cellIndex+1], WEST);
        }else{
            DEL_WALL(cases[cellIndex], EAST);
            DEL_WALL(cases[cellIndex+1], WEST);
        }
        break;
    case 'S':
        if(HAS_WALL(cases[cellIndex], SOUTH)==0){
            SET_WALL(cases[cellIndex], SOUTH);
            SET_WALL(cases[cellIndex+16], NORTH);
        }else{
            DEL_WALL(cases[cellIndex], SOUTH);
            DEL_WALL(cases[cellIndex+16], NORTH);
        }
        break;
    case 'W':
        if(HAS_WALL(cases[cellIndex], WEST)==0){
            SET_WALL(cases[cellIndex], WEST);
            SET_WALL(cases[cellIndex-1], EAST);
        }else{
            DEL_WALL(cases[cellIndex], WEST);
            DEL_WALL(cases[cellIndex-1], EAST);
        }
        break;
    }
    notifyObserver();
}

void Board::removeWall(int pos){
    if(HAS_WALL(cases[pos], NORTH)!=0){
        DEL_WALL(cases[pos], NORTH);
        DEL_WALL(cases[pos-16], SOUTH);
    }
    if(HAS_WALL(cases[pos], EAST)!=0){
        DEL_WALL(cases[pos], EAST);
        DEL_WALL(cases[pos+1], WEST);
    }
    if(HAS_WALL(cases[pos], SOUTH)!=0){
        DEL_WALL(cases[pos], SOUTH);
        DEL_WALL(cases[pos+16], NORTH);
    }
    if(HAS_WALL(cases[pos], WEST)!=0){
        DEL_WALL(cases[pos], WEST);
        DEL_WALL(cases[pos-1], EAST);
    }

    for(int i=0;i<16;i++){
        SET_WALL(cases[i], NORTH);
        SET_WALL(cases[i+16*15], SOUTH);
        SET_WALL(cases[i*16], WEST);
        SET_WALL(cases[i*16+15], EAST);
    }
    SET_WALL(cases[151],NORTH);
    SET_WALL(cases[152],NORTH);
    SET_WALL(cases[103],SOUTH);
    SET_WALL(cases[104],SOUTH);
    SET_WALL(cases[118],EAST);
    SET_WALL(cases[134],EAST);
    SET_WALL(cases[121],WEST);
    SET_WALL(cases[137],WEST);
}


int Board::getBoardSize() {
    return BOARD_SIZE;
}

void Board::moveObject(int id, int pos) {
    this->objectives.at(id)=pos;
    notifyObserver();
}

void Board::moveRobot(int id, int pos) {
    this->robots_move.at(id)=pos;
    notifyObserver();
}

void Board::reset(){
    std::cout<<"1.0"<<std::endl;
    mouvement=0;
    objJeu=-1;

    for(int i=0;i<255;i++){
        DEL_WALL(cases[i], NORTH);
        DEL_WALL(cases[i], SOUTH);
        DEL_WALL(cases[i], EAST);
        DEL_WALL(cases[i], WEST);
    }

    for(int i=0;i<16;i++){
        SET_WALL(cases[i], NORTH);
        SET_WALL(cases[i+16*15], SOUTH);
        SET_WALL(cases[i*16], WEST);
        SET_WALL(cases[i*16+15], EAST);
    }

    std::cout<<"2.0"<<std::endl;
    SET_WALL(cases[151],NORTH);
    SET_WALL(cases[152],NORTH);
    SET_WALL(cases[103],SOUTH);
    SET_WALL(cases[104],SOUTH);
    SET_WALL(cases[118],EAST);
    SET_WALL(cases[134],EAST);
    SET_WALL(cases[121],WEST);
    SET_WALL(cases[137],WEST);

    std::cout<<"3.0"<<std::endl;
    for(int i=0;i<17;i++){
        this->objectives.at(i)=-1;
    }

    for(int i=0;i<5;i++){
        this->robots_move.at(i)=-1;
    }

    std::cout<<"4.0"<<std::endl;
    notifyObserver();
}
