//#ifndef VIEWPLATEAU_H
//#define VIEWPLATEAU_H

//#include <QWidget>

//class viewPlateau : public QObject
//{
//    Q_OBJECT
//private:
//    QWidget *widg2;
//public:
//    viewPlateau(QWidget *parent);
//};

//#endif // VIEWPLATEAU_H

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

public:
    viewPlateau(Board* = nullptr);
    void updateModel();
    void drawObjectives(int targetCell, const QString& imagePath, int id);
    void drawWall();
    void drawRobot(int targetCell, const QString& imagePath, int id);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
};


