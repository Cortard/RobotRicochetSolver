#include "viewboard.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

ViewBoard::ViewBoard(Board* board) : QGraphicsScene(), Observer()
{

    this->board=board;
    board->addObserver(this);
//    (new ControllerAddObj(board))->control(0,0);
//    std::cout<< "avant call" <<std::endl;
//    addImageToCell(board->objectives.at(0), ":/img/balle.png", 0);
    updateModel();
    update();
}

void ViewBoard::updateModel()
{
    clear();

    const int cellSize = 25;
    const int rowCount = 16;
    const int colCount = 16;

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            if (row >= 7 && row < 9 && col >= 7  && col < 9) {
                continue;
            }

            int x = col * cellSize;
            int y = row * cellSize;

            // Ligne horizontale supérieure
            QGraphicsLineItem *topLine = new QGraphicsLineItem(x, y, x + cellSize, y);
            topLine->setPen(QPen(Qt::black, 1));
            topLine->setAcceptHoverEvents(true);
            addItem(topLine);

            // Ligne verticale gauche
            QGraphicsLineItem *leftLine = new QGraphicsLineItem(x, y, x, y + cellSize);
            leftLine->setPen(QPen(Qt::black, 1));
            topLine->setAcceptHoverEvents(true);
            addItem(leftLine);

            // Ligne horizontale inférieure
            QGraphicsLineItem *bottomLine = new QGraphicsLineItem(x, y + cellSize, x + cellSize, y + cellSize);
            bottomLine->setPen(QPen(Qt::black, 1));
            topLine->setAcceptHoverEvents(true);
            addItem(bottomLine);

            // Ligne verticale droite
            QGraphicsLineItem *rightLine = new QGraphicsLineItem(x + cellSize, y, x + cellSize, y + cellSize);
            rightLine->setPen(QPen(Qt::black, 1));
            topLine->setAcceptHoverEvents(true);
            addItem(rightLine);

            if(temp==0){
                lines.push_back(topLine);
                lines.push_back(leftLine);
                lines.push_back(bottomLine);
                lines.push_back(rightLine);

                int cellIndex = col + row * colCount;
                cellMap[cellIndex] = topLine;
                cellMap[cellIndex + 256] = leftLine;
                cellMap[cellIndex + 512] = bottomLine;
                cellMap[cellIndex + 768] = rightLine;

                cellImageMap[cellIndex] = false;
                temp++;
            }
        }
    }

    for(int i=0;i<16;i++){
        if(board->objectives.at(i)!=-1){
            addImageToCell(board->objectives.at(i), ":/img/balle.png", i);
        }
    }

    update();
}

void ViewBoard::addImageToCell(int targetCell, const QString& imagePath, int id)
{
    QPixmap pixmap(imagePath);
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
    pixmapItem->setScale(25.0 / pixmap.width());

    int col = targetCell % 16;
    int row = targetCell / 16;

    pixmapItem->setPos(col * 25, row * 25);
    pixmapItem->setFlag(QGraphicsItem::ItemIsMovable);

    pixmapItem->setData(0, id);

    addItem(pixmapItem);

    cellImageMap[targetCell] = true;
}


void ViewBoard::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        QPointF mousePos = mouseEvent->scenePos();
//        const qreal tolerance = 10.0;
//        for (QGraphicsLineItem* line : lines) {
//            QLineF lineGeometry = line->line();
//            if (QLineF(mousePos, lineGeometry.center()).length() < tolerance) {
//                QPen pen = line->pen();
//                if(pen.width()!=3){
//                    pen.setWidth(3);
//                }else{
//                    pen.setWidth(1);
//                }
//                line->setPen(pen);
//                break;
//            }
//        }
        QGraphicsItem* clickedItem = itemAt(mousePos, QTransform());
            if (clickedItem && clickedItem->type() == QGraphicsPixmapItem::Type) {
                draggedPixmapItem = dynamic_cast<QGraphicsPixmapItem*>(clickedItem);
                initialPos=mouseEvent->scenePos();
                if (draggedPixmapItem) {
                    previousPos = mousePos;
                }
            }
    }
    update();
}

void ViewBoard::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{

    if (draggedPixmapItem) {
            QPointF delta = mouseEvent->scenePos() - previousPos;
            draggedPixmapItem->setPos(draggedPixmapItem->pos() + delta);
            previousPos = mouseEvent->scenePos();
    }

}

void ViewBoard::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    if (draggedPixmapItem) {
            int id = draggedPixmapItem->data(0).toInt();
            draggedPixmapItem = nullptr;
            int cellIndex = static_cast<int>(mouseEvent->scenePos().x() / 25) + static_cast<int>(mouseEvent->scenePos().y() / 25) * 16;
            (new ControllerMoveObj(board))->control(id,cellIndex);
    }
}
