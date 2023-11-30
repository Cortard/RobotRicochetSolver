#include "controller.h"
#include "board.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

ControllerAddObj::ControllerAddObj(Board* bd) : board(bd)
{}

void ControllerAddObj::control()
{
    if (board == nullptr) return;

    for(int i=0;i<17;i++){
        if(board->objectives.at(i)==-1){
            board->addObjective(i, 135);
            return ;
        }
    }
}

ControllerMoveObj::ControllerMoveObj(Board* bd) : board(bd)
{}

void ControllerMoveObj::control(int id, int pos)
{
    if (board == nullptr) return;

    if(pos!=135 && pos!=136 && pos!=119 && pos!=120){
        board->moveObject(id,pos);
    }else{
        board->notifyObserver();
    }
}

ControllerAddWall::ControllerAddWall(Board* bd) : board(bd)
{}

void ControllerAddWall::control()
{
    if (board == nullptr) return;
}
