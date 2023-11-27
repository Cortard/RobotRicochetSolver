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
    std::map<int, QGraphicsLineItem*> cellMap;
    std::map<int, bool> cellImageMap;
    QPointF previousPos;
    QPointF initialPos;
    QGraphicsPixmapItem* draggedPixmapItem = nullptr;

public:
    ViewBoard();
    void updateModel();
    void addImageToCell(int targetCell, const QString& imagePath);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
};


