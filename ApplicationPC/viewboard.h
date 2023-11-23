#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTreeWidget>


class ViewBoard : public QGraphicsScene
{
    Q_OBJECT
private:

    QVector<QGraphicsItem*> selected;
    QVector<QGraphicsItem*> tools;
    QPointF mousePos;
    QString toolbox;
    QVector<QGraphicsLineItem*> lines;

public:
    ViewBoard();
    void updateModel();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);


};


