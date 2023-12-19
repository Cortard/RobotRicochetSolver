#include "viewboard.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

ViewBoard::ViewBoard(Board* board) : QGraphicsScene(), Observer()
{
    this->board=board;
    board->addObserver(this);
    temp=0;
    objImg[0]=":/img/lunerouge.png";
    objImg[1]=":/img/trianglerouge.png";
    objImg[2]=":/img/satelliterouge.png";
    objImg[3]=":/img/etoilerouge.png";
    objImg[4]=":/img/lunevert.png";
    objImg[5]=":/img/trianglevert.png";
    objImg[6]=":/img/planetevert.png";
    objImg[7]=":/img/etoilevert.png";
    objImg[8]=":/img/lunebleu.png";
    objImg[9]=":/img/trianglebleu.png";
    objImg[10]=":/img/planetebleu.png";
    objImg[11]=":/img/etoilebleu.png";
    objImg[12]=":/img/lunejaune.png";
    objImg[13]=":/img/trianglejaune.png";
    objImg[14]=":/img/planetejaune.png";
    objImg[15]=":/img/etoilejaune.png";
    objImg[16]=":/img/portail.png";

    robotImg[0]=":/img/robotrouge.png";
    robotImg[1]=":/img/robotvert.png";
    robotImg[2]=":/img/robotbleu.png";
    robotImg[3]=":/img/robotjaune.png";
    robotImg[4]=":/img/robotnoir.png";

    updateModel();
    update();
}

void ViewBoard::updateModel()
{
    clear();

    for(int i=0;i<17;i++){
        if(board->objectives.at(i)!=-1){
            drawObjectives(board->objectives.at(i), objImg[i], i);
        }
    }
    for(int i=0;i<5;i++){
        if(board->robots.at(i)!=-1){
            drawRobot(board->robots.at(i), robotImg[i], i);
        }
    }

    setSceneRect(0, 0, CellSize*16, CellSize*16);
    drawWall();
    update();
}

void ViewBoard::drawWall()
{
    const int rowCount = 16;
    const int colCount = 16;

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            if (row >= 7 && row < 9 && col >= 7  && col < 9) {
                continue;
            }

            int x = col * CellSize;
            int y = row * CellSize;

            // Ligne horizontale supérieure
            QGraphicsLineItem *topLine = new QGraphicsLineItem(x, y, x + CellSize, y);
            if(temp==1){
                if (HAS_WALL(board->cases[col + row * colCount], NORTH) == 1){
                    topLine->setPen(QPen(Qt::black, 3));
                }else{
                    topLine->setPen(QPen(Qt::black, 1));
                }
            }else{
                topLine->setPen(QPen(Qt::black, 1));
            }
            if(y<CellSize || (x>6*CellSize && x<9*CellSize) && (y>6*CellSize && y<10*CellSize)){
                topLine->setPen(QPen(Qt::black, 3));
            }
            topLine->setAcceptHoverEvents(true);
            addItem(topLine);

            // Ligne verticale gauche
            QGraphicsLineItem *leftLine = new QGraphicsLineItem(x, y, x, y + CellSize);
            if(temp==1){
                if (HAS_WALL(board->cases[col + row * colCount], WEST) == 8){
                    leftLine->setPen(QPen(Qt::black, 3));
                }else{
                    leftLine->setPen(QPen(Qt::black, 1));
                }
            }else{
                leftLine->setPen(QPen(Qt::black, 1));
            }
            if(x<CellSize || (x>6*CellSize && x<10*CellSize) && (y>6*CellSize && y<9*CellSize)){
                leftLine->setPen(QPen(Qt::black, 3));
            }
            leftLine->setAcceptHoverEvents(true);
            addItem(leftLine);

            // Ligne horizontale inférieure
            QGraphicsLineItem *bottomLine = new QGraphicsLineItem(x, y + CellSize, x + CellSize, y + CellSize);
            if(temp==1){
                if (HAS_WALL(board->cases[col + row * colCount], SOUTH) == 4){
                    bottomLine->setPen(QPen(Qt::black, 3));
                }else{
                    bottomLine->setPen(QPen(Qt::black, 1));
                }
            }else{
                bottomLine->setPen(QPen(Qt::black, 1));
            }
            if(y>14*CellSize || (x>6*CellSize && x<9*CellSize) && (y>5*CellSize && y<9*CellSize)){
                bottomLine->setPen(QPen(Qt::black, 3));
            }
            bottomLine->setAcceptHoverEvents(true);
            addItem(bottomLine);

            // Ligne verticale droite
            QGraphicsLineItem *rightLine = new QGraphicsLineItem(x + CellSize, y, x + CellSize, y + CellSize);
            if(temp==1){
                if (HAS_WALL(board->cases[col + row * colCount], EAST) == 2){
                    rightLine->setPen(QPen(Qt::black, 3));
                }else{
                    rightLine->setPen(QPen(Qt::black, 1));
                }
            }else{
                rightLine->setPen(QPen(Qt::black, 1));
            }
            if(x>14*CellSize || (x>5*CellSize && x<9*CellSize) && (y>6*CellSize && y<9*CellSize)){
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

    pixmapItem->setPos(col * CellSize, row * CellSize);
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

    pixmapItem->setPos(col * CellSize, row * CellSize);
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

        int col = static_cast<int>(mousePos.x() / CellSize);
        int row = static_cast<int>(mousePos.y() / CellSize);

        QPointF cellTopLeft(col * CellSize, row * CellSize);

        qreal dxLeft = mousePos.x() - cellTopLeft.x();
        qreal dxRight = (cellTopLeft.x() + CellSize) - mousePos.x();
        qreal dyTop = mousePos.y() - cellTopLeft.y();
        qreal dyBottom = (cellTopLeft.y() + CellSize) - mousePos.y();

        qreal minDistance = std::min({dxLeft, dxRight, dyTop, dyBottom});

        qreal threshold = 25.0 / 2.0;

        if (minDistance < threshold && !draggedPixmapItem)
        {
            if (minDistance == dxLeft && mousePos.x()>CellSize)
            {
                (new ControllerAddWall(board))->control(mousePos.x(), mousePos.y(), 'W');
            }
            if (minDistance == dxRight && mousePos.x()<CellSize*15)
            {
                (new ControllerAddWall(board))->control(mousePos.x(), mousePos.y(), 'E');
            }
            if (minDistance == dyTop && mousePos.y()>CellSize)
            {
                (new ControllerAddWall(board))->control(mousePos.x(), mousePos.y(), 'N');
            }
            if (minDistance == dyBottom && mousePos.y()<CellSize*15)
            {
                (new ControllerAddWall(board))->control(mousePos.x(), mousePos.y(), 'S');
            }
        }
    }
    if (mouseEvent->button() == Qt::MiddleButton) {
        int col = static_cast<int>(mouseEvent->scenePos().x() / CellSize);
        int row = static_cast<int>(mouseEvent->scenePos().y() / CellSize);

        int cellIndex = col + row * 16;

        (new ControllerRemoveRobot(board))->control(cellIndex);
        (new ControllerRemoveObj(board))->control(cellIndex);
    }
    if(mouseEvent->button() == Qt::RightButton){
        QPointF mousePos = mouseEvent->scenePos();
        QGraphicsItem* clickedItem = itemAt(mousePos, QTransform());
        if (clickedItem && clickedItem->type() == QGraphicsPixmapItem::Type) {
            QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(clickedItem);
            if (pixmapItem->data(1).toInt() == QGraphicsPixmapItem::UserType + 2) {
                int id = pixmapItem->data(0).toInt();
                if(clickdroit==0){
                    qDebug() << "Clic droit sur l'objectif avec l'ID : " << id;
                    clickdroit++;
                    board->objJeu=id;
                }
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
        int col = static_cast<int>(mouseEvent->scenePos().x() / CellSize);
        int row = static_cast<int>(mouseEvent->scenePos().y() / CellSize);

        int initialCol = static_cast<int>(initialPos.x() / CellSize);
        int initialRow = static_cast<int>(initialPos.y() / CellSize);

        int initialCell = initialCol + initialRow *16;

        int cellIndex = col + row * 16;
        if(cellImageMap[cellIndex]==false){
            if (draggedPixmapItem->data(1).toInt() == QGraphicsPixmapItem::UserType + 1) {
                // C'est un robot
                (new ControllerMoveRobot(board))->control(id, cellIndex);
            } else if (draggedPixmapItem->data(1).toInt() == QGraphicsPixmapItem::UserType + 2) {
                // C'est un objectif
                (new ControllerMoveObj(board))->control(id, cellIndex);
            }
        }else{
            if (draggedPixmapItem->data(1).toInt() == QGraphicsPixmapItem::UserType + 1) {
                // C'est un robot
                (new ControllerMoveRobot(board))->control(id, initialCell);
            } else if (draggedPixmapItem->data(1).toInt() == QGraphicsPixmapItem::UserType + 2) {
                // C'est un objectif
                (new ControllerMoveObj(board))->control(id, initialCell);
            }
        }

        // Réinitialiser draggedPixmapItem après avoir terminé le traitement
        draggedPixmapItem = nullptr;
    }
}
