#include "viewboard.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

ViewBoard::ViewBoard(Board* board) : QGraphicsScene(), Observer()
{
    this->board=board;
    board->addObserver(this);
    temp=0;
    updateModel();
    update();
}

void ViewBoard::updateModel()
{
    clear();

    for(int i=0;i<17;i++){
        if(board->objectives.at(i)!=-1){
            drawObjectives(board->objectives.at(i), ":/img/balle.png", i);
        }
    }
    for(int i=0;i<4;i++){
        if(board->robots.at(i)!=-1){
            drawRobot(board->robots.at(i), ":/img/tennis.png", i);
        }
    }

    setSceneRect(0, 0, 25*16, 25*16);
    drawWall();
    update();
}

void ViewBoard::drawWall()
{
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
            if(temp==1){
                if (HAS_WALL(board->cases[col + row * colCount], NORTH) == 1){
                    topLine->setPen(QPen(Qt::black, 3));
                }else{
                    topLine->setPen(QPen(Qt::black, 1));
                }
            }else{
                topLine->setPen(QPen(Qt::black, 1));
            }
            if(y<25 || (x>6*25 && x<9*25) && (y>6*25 && y<10*25)){
                topLine->setPen(QPen(Qt::black, 3));
            }
            topLine->setAcceptHoverEvents(true);
            addItem(topLine);

            // Ligne verticale gauche
            QGraphicsLineItem *leftLine = new QGraphicsLineItem(x, y, x, y + cellSize);
            if(temp==1){
                if (HAS_WALL(board->cases[col + row * colCount], WEST) == 8){
                    leftLine->setPen(QPen(Qt::black, 3));
                }else{
                    leftLine->setPen(QPen(Qt::black, 1));
                }
            }else{
                leftLine->setPen(QPen(Qt::black, 1));
            }
            if(x<25 || (x>6*25 && x<10*25) && (y>6*25 && y<9*25)){
                leftLine->setPen(QPen(Qt::black, 3));
            }
            leftLine->setAcceptHoverEvents(true);
            addItem(leftLine);

            // Ligne horizontale inférieure
            QGraphicsLineItem *bottomLine = new QGraphicsLineItem(x, y + cellSize, x + cellSize, y + cellSize);
            if(temp==1){
                if (HAS_WALL(board->cases[col + row * colCount], SOUTH) == 4){
                    bottomLine->setPen(QPen(Qt::black, 3));
                }else{
                    bottomLine->setPen(QPen(Qt::black, 1));
                }
            }else{
                bottomLine->setPen(QPen(Qt::black, 1));
            }
            if(y>14*25 || (x>6*25 && x<9*25) && (y>5*25 && y<9*25)){
                bottomLine->setPen(QPen(Qt::black, 3));
            }
            bottomLine->setAcceptHoverEvents(true);
            addItem(bottomLine);

            // Ligne verticale droite
            QGraphicsLineItem *rightLine = new QGraphicsLineItem(x + cellSize, y, x + cellSize, y + cellSize);
            if(temp==1){
                if (HAS_WALL(board->cases[col + row * colCount], EAST) == 2){
                    rightLine->setPen(QPen(Qt::black, 3));
                }else{
                    rightLine->setPen(QPen(Qt::black, 1));
                }
            }else{
                rightLine->setPen(QPen(Qt::black, 1));
            }
            if(x>14*25 || (x>5*25 && x<9*25) && (y>6*25 && y<9*25)){
                rightLine->setPen(QPen(Qt::black, 3));
            }
            rightLine->setAcceptHoverEvents(true);
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
            }
        }
    }

    temp=1;
}

void ViewBoard::drawObjectives(int targetCell, const QString& imagePath, int id)
{
    QPixmap pixmap(imagePath);
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
    pixmapItem->setScale(25.0 / pixmap.width());

    int col = targetCell % 16;
    int row = targetCell / 16;

    pixmapItem->setPos(col * 25, row * 25);
    pixmapItem->setFlag(QGraphicsItem::ItemIsMovable);

    pixmapItem->setData(0, id);
    pixmapItem->setData(1, QGraphicsPixmapItem::UserType + 2);
    addItem(pixmapItem);

    cellImageMap[targetCell] = true;
}

void ViewBoard::drawRobot(int targetCell, const QString& imagePath, int id)
{
    QPixmap pixmap(imagePath);
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
    pixmapItem->setScale(25.0 / pixmap.width());

    int col = targetCell % 16;
    int row = targetCell / 16;

    pixmapItem->setPos(col * 25, row * 25);
    pixmapItem->setFlag(QGraphicsItem::ItemIsMovable);

    pixmapItem->setData(0, id);
    pixmapItem->setData(1, QGraphicsPixmapItem::UserType + 1);

    addItem(pixmapItem);

    cellImageMap[targetCell] = true;
}

void ViewBoard::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        QPointF mousePos = mouseEvent->scenePos();

        QGraphicsItem* clickedItem = itemAt(mousePos, QTransform());
        if (clickedItem && clickedItem->type() == QGraphicsPixmapItem::Type) {
            draggedPixmapItem = dynamic_cast<QGraphicsPixmapItem*>(clickedItem);
            initialPos=mouseEvent->scenePos();
            if (draggedPixmapItem) {
                previousPos = mousePos;
            }
        }

        int col = static_cast<int>(mousePos.x() / 25);
        int row = static_cast<int>(mousePos.y() / 25);

        QPointF cellTopLeft(col * 25, row * 25);

        qreal dxLeft = mousePos.x() - cellTopLeft.x();
        qreal dxRight = (cellTopLeft.x() + 25) - mousePos.x();
        qreal dyTop = mousePos.y() - cellTopLeft.y();
        qreal dyBottom = (cellTopLeft.y() + 25) - mousePos.y();

        qreal minDistance = std::min({dxLeft, dxRight, dyTop, dyBottom});

        qreal threshold = 25.0 / 2.0;

        if (minDistance < threshold && !draggedPixmapItem)
        {
            if (minDistance == dxLeft && mousePos.x()>25)
            {
                (new ControllerAddWall(board))->control(mousePos.x(), mousePos.y(), 'W');
            }
            if (minDistance == dxRight && mousePos.x()<25*15)
            {
                (new ControllerAddWall(board))->control(mousePos.x(), mousePos.y(), 'E');
            }
            if (minDistance == dyTop && mousePos.y()>25)
            {
                (new ControllerAddWall(board))->control(mousePos.x(), mousePos.y(), 'N');
            }
            if (minDistance == dyBottom && mousePos.y()<25*15)
            {
                (new ControllerAddWall(board))->control(mousePos.x(), mousePos.y(), 'S');
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
        int col = static_cast<int>(mouseEvent->scenePos().x() / 25);
        int row = static_cast<int>(mouseEvent->scenePos().y() / 25);
        int cellIndex = col + row * 16;

        if (draggedPixmapItem->data(1).toInt() == QGraphicsPixmapItem::UserType + 1) {
            // C'est un robot
            (new ControllerMoveRobot(board))->control(id, cellIndex);
        } else if (draggedPixmapItem->data(1).toInt() == QGraphicsPixmapItem::UserType + 2) {
            // C'est un objectif
            (new ControllerMoveObj(board))->control(id, cellIndex);
        }

        // Réinitialiser draggedPixmapItem après avoir terminé le traitement
        draggedPixmapItem = nullptr;
    }
}


