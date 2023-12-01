#pragma once
#include <QPointF>
#include "board.h"
#include <QGraphicsItem>

class ControllerAddObj
{
    Board* board;
public:
    ControllerAddObj(Board* = nullptr);
    void control();
};

class ControllerMoveObj
{
    Board* board;
public:
    ControllerMoveObj(Board* = nullptr);
    void control(int id, int pos);
};

class ControllerAddWall
{
    Board* board;
public:
    ControllerAddWall(Board* = nullptr);
    void control(int x, int y, char dir);
};
