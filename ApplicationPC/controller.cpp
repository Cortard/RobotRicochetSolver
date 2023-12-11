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

    if(pos!=135 && pos!=136 && pos!=119 && pos!=120 && pos>=0 && pos<256){
        board->moveObject(id,pos);
    }else{
        board->notifyObserver();
    }
}

ControllerAddWall::ControllerAddWall(Board* bd) : board(bd)
{}

void ControllerAddWall::control(int x, int y, char dir)
{
    if (board == nullptr) return;

    board->addWall(x, y, dir);
}

ControllerAddRobot::ControllerAddRobot(Board* bd) : board(bd)
{}

void ControllerAddRobot::control(){
    if (board == nullptr) return;

    for(int i=0;i<17;i++){
        if(board->robots.at(i)==-1){
            board->addRobot(i, 136);
            return ;
        }
    }
}

ControllerMoveRobot::ControllerMoveRobot(Board* bd) : board(bd)
{}

void ControllerMoveRobot::control(int id, int pos)
{
    if (board == nullptr) return;

    if(pos!=135 && pos!=136 && pos!=119 && pos!=120 && pos>=0 && pos<256){
        board->moveRobot(id,pos);
    }else{
        board->notifyObserver();
    }
}

ControllerRemoveRobot::ControllerRemoveRobot(Board* bd) : board(bd)
{}

void ControllerRemoveRobot::control(int pos){
    if (board == nullptr) return;

    board->removeRobot(pos);
}

ControllerRemoveObj::ControllerRemoveObj(Board* bd) : board(bd)
{}

void ControllerRemoveObj::control(int pos){
    if (board == nullptr) return;

    board->removeObj(pos);
}
