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
}

int Board::getIndex(int x, int y) const {
    return x + y * BOARD_SIZE;
}

void Board::addObjective(int id, int pos)
{
    this->objectives.at(id)=pos;
    notifyObserver();
}


void Board::addWall(int x, int y, char dir) {
}

int Board::getBoardSize() {
    return BOARD_SIZE;
}

void Board::moveObject(int id, int pos)
{
    this->objectives.at(id)=pos;
    notifyObserver();
}

