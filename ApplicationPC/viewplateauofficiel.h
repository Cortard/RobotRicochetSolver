#pragma once
#include "board.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "controller.h"

class ViewPlateauOfficiel : public QGraphicsScene, public Observer
{
    Q_OBJECT

private:
    Board* board;
    std::map<QPointF, QString, std::function<bool(const QPointF&, const QPointF&)>> imagePositions;
    int click=0;
    std::map<QPointF, QString>::iterator it;
    QPointF secondClickPos;
    int col=-1;

public:
    ViewPlateauOfficiel(Board* = nullptr);
    void updateModel();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
};
