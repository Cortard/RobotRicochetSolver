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

    int position=-1;

public:
    ViewPlateauOfficiel(Board* = nullptr);
    void updateModel();

    void deleteTopRight(Board* board);
    void deleteTopLeft(Board* board);
    void deleteBotRight(Board* board);
    void deleteBotLeft(Board* board);

    void constructPart1(Board* board, int pos);
    void constructPart2(Board* board, int pos);
    void constructPart3(Board* board, int pos);
    void constructPart4(Board* board, int pos);
    void constructPart5(Board* board, int pos);
    void constructPart6(Board* board, int pos);
    void constructPart7(Board* board, int pos);
    void constructPart8(Board* board, int pos);
    void constructPart9(Board* board, int pos);
    void constructPart10(Board* board, int pos);
    void constructPart11(Board* board, int pos);
    void constructPart12(Board* board, int pos);
    void constructPart13(Board* board, int pos);
    void constructPart14(Board* board, int pos);
    void constructPart15(Board* board, int pos);
    void constructPart16(Board* board, int pos);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
};
