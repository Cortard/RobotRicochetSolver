#include "board.h"
#include <iostream>
#include "observer.h"

Board::Board() {
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i) {
        cases[i] = 0;
    }
    for(int i=0;i<17;i++){
        this->objectives.insert(std::pair<int,int>(i,-1));
    }
    for(int i=0;i<5;i++){
        this->robots.insert(std::pair<int,int>(i,-1));
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

int Board::getIndex(int x, int y) const {
    return (static_cast<int>(x / 25) + static_cast<int>(y / 25) * 16);
}

void Board::addObjective(int id, int pos)
{
    this->objectives.at(id)=pos;
    notifyObserver();
}

void Board::removeObj(int pos)
{
    std::for_each(this->objectives.begin(), this->objectives.end(),
                  [pos](auto& pair) {
        if (pair.second == pos) {
            pair.second = -1;
        }
    });
    notifyObserver();
}

void Board::addRobot(int id, int pos)
{
    this->robots.at(id)=pos;
    notifyObserver();
}

void Board::removeRobot(int pos)
{
    std::for_each(this->robots.begin(), this->robots.end(),
                  [pos](auto& pair) {
        if (pair.second == pos) {
            pair.second = -1;
        }
    });
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

int Board::getBoardSize() {
    return BOARD_SIZE;
}

void Board::moveObject(int id, int pos)
{
    this->objectives.at(id)=pos;
    notifyObserver();
}

void Board::moveRobot(int id, int pos)
{
    this->robots.at(id)=pos;
    notifyObserver();
}
