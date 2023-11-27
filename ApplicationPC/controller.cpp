#include "controller.h"
#include "board.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

ControllerMoveShape::ControllerMoveShape(Board* sm) : board(sm)
{}

void ControllerMoveShape::control(const QVector<QGraphicsItem*>& items)
{
    if (board == nullptr) return;

    for (QGraphicsItem* item : items)
    {
        QVariant variant = item->data(0);
        int id = variant.toInt();

        bool selected = board->selectShape(id);
        if (selected)
        {
            QRectF rect = item->boundingRect();
            board->moveShape(item->scenePos() + rect.center());
        }
    }

    board->notifyObserver();
}
