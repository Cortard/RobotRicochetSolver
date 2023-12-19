#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTreeWidget>
#include "controller.h"
#include "board.h"

class viewPlateau : public QGraphicsScene, public Observer
{
    Q_OBJECT
private:
    int CellSize =25;
    int TailleBoard = 16;
    QVector<QGraphicsItem*> selected;
    QVector<QGraphicsItem*> tools;
    QPointF mousePos;
    QString toolbox;
    QVector<QGraphicsLineItem*> lines;
    std::map<int, QGraphicsLineItem*> cellMap;
    std::map<int, bool> cellImageMap;
    QString objImg[17];
    QString robotImg[5];
    QPointF previousPos;
    QPointF initialPos;
    QGraphicsPixmapItem* draggedPixmapItem = nullptr;
    int temp = 0;
    Board* board;
    int click=0;
    int direction=-1;
    int col=0;
    int row=0;
    int id=-1;
    int compPos=0;
    int selectedRow = -1;
    int selectedCol = -1;
    QList<QGraphicsRectItem*> selectionSquares;
    int robotId = -1;


public:
    viewPlateau(Board* = nullptr);
    void updateModel();
    void drawObjectives(int targetCell, const QString& imagePath, int id);
    void drawWall();
    void drawRobot(int targetCell, const QString& imagePath, int id);
    void drawSelectionSquare(int row, int col, int id);
    void clearSelectionSquares();
signals:
    void movementOccurred();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
};


