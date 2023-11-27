#pragma once
#include <QPointF>
#include "board.h"

class ControllerMoveShape
{
    Board* board;
public:
    ControllerMoveShape(Board* = nullptr);
    void control(const QVector<QGraphicsItem *> &);
};
