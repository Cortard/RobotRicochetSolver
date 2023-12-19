#include "viewplateau.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

viewPlateau::viewPlateau(Board* board) : QGraphicsScene(), Observer()
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

    drawWall();
    updateModel();
    update();
}

void viewPlateau::updateModel()
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

void viewPlateau::drawWall()
{
    const int rowCount = 16;
    const int colCount = 16;

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {

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

void viewPlateau::drawObjectives(int targetCell, const QString& imagePath, int id)
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

void viewPlateau::drawRobot(int targetCell, const QString& imagePath, int id)
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

void viewPlateau::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    for (const auto& robot : board->robots) {
        if (robot.second == board->objectives[board->objJeu]) {
            robotId = robot.first;
            break;
        }
    }

    if (robotId==-1 || (board->objJeu >= 0 && board->objJeu <= 3 && robotId!=0) || (board->objJeu >= 4 && board->objJeu <= 7 && robotId!=1) || (board->objJeu >= 8 && board->objJeu <= 11 && robotId!=2) || (robotId != 3 && board->objJeu >= 12 && board->objJeu <= 15)) {

        if (mouseEvent->button() == Qt::LeftButton){
            QPointF mousePos = mouseEvent->scenePos();

            QGraphicsItem* clickedItem = itemAt(mousePos, QTransform());
            if (clickedItem && clickedItem->type() == QGraphicsPixmapItem::Type) {
                draggedPixmapItem = dynamic_cast<QGraphicsPixmapItem*>(clickedItem);
            }

            click++;
            if(click==1){
                col = static_cast<int>(mousePos.x() / CellSize);
                row = static_cast<int>(mousePos.y() / CellSize);
                selectedRow = row;
                selectedCol = col;
                id = draggedPixmapItem->data(0).toInt();
                drawSelectionSquare(selectedRow, selectedCol, id);
            }
            int pos = col + row * 16;
            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });

            if (it != board->robots.end()) {
                if (click == 2){
                    QPointF secondMouse = mouseEvent->scenePos();
                    clearSelectionSquares();

                    int col2 = static_cast<int>(secondMouse.x() / CellSize);
                    int row2 = static_cast<int>(secondMouse.y() / CellSize);

                    if (row2 == row && col2 < col)
                    {
                        for(int i=col;i>=0;i--){
                            if (HAS_WALL(board->cases[i + row * 16], WEST) == 8){
                                compPos = (i + row * 16);
                                break;
                            }
                        }

                        int targetRow = row;
                        int targetCol = -1;

                        for (int i = col-1 ; i >= 0 ; i--){
                            int pos = i + row * 16;
                            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                                   [pos](const auto& pair) { return pair.second == pos; });
                            if (it != board->robots.end()){
                                targetCol = i;
                                break;
                            }
                        }

                        int targetPos = targetCol + targetRow * 16;

                        if(targetPos >= compPos && targetCol!=-1 ){
                            (new ControllerMoveRobot(board))->control(id, targetPos+1);
                        }else{
                            (new ControllerMoveRobot(board))->control(id, compPos);
                        }
                        click = 0;
                        emit movementOccurred();
                        return;
                    }
                    else if (row2 == row && col2 > col)
                    {
                        for(int i=col;i<16;i++){
                            if (HAS_WALL(board->cases[i + row * 16], EAST) == 2){
                                compPos = (i + row * 16);
                                break;
                            }
                        }

                        int targetRow = row;
                        int targetCol = -1;

                        for (int i = col+1 ; i <= 16 ; i++){
                            int pos = i + row * 16;

                            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                                   [pos](const auto& pair) { return pair.second == pos; });
                            if (it != board->robots.end()){
                                targetCol = i;
                                break;
                            }
                        }

                        int targetPos = targetCol + targetRow * 16;

                        if(targetPos <= compPos && targetCol!=-1 ){
                            (new ControllerMoveRobot(board))->control(id, targetPos-1);
                        }else{
                            (new ControllerMoveRobot(board))->control(id, compPos);
                        }
                        click = 0;
                        emit movementOccurred();
                        return;
                    }
                    else if (row2 > row && col2 == col)
                    {
                        for(int i=row;i<=16;i++){
                            if (HAS_WALL(board->cases[col + i * 16], SOUTH) == 4){
                                compPos = (col + i * 16);
                                break;
                            }
                        }

                        int targetRow = -1;
                        int targetCol = col;

                        for (int i = row+1 ; i <= 16 ; i++){
                            int pos = col + i * 16;
                            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                                   [pos](const auto& pair) { return pair.second == pos; });
                            if (it != board->robots.end()){
                                targetRow = i;
                                break;
                            }
                        }

                        int targetPos = targetCol + targetRow * 16;

                        if(targetPos <= compPos && targetRow!=-1 ){
                            (new ControllerMoveRobot(board))->control(id, targetPos-16);
                        }else{
                            (new ControllerMoveRobot(board))->control(id, compPos);
                        }
                        click = 0;
                        emit movementOccurred();
                        return;
                    }
                    else if (row2 < row && col2 == col)
                    {
                        for(int i=row;i>=0;i--){
                            if (HAS_WALL(board->cases[col + i * 16], NORTH) == 1){
                                compPos = (col + i * 16);
                                break;
                            }
                        }

                        int targetRow = -1;
                        int targetCol = col;

                        for (int i = 0; i < row ; i++){
                            int pos = col + i * 16;
                            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                                   [pos](const auto& pair) { return pair.second == pos; });
                            if (it != board->robots.end()){
                                targetRow = i;
                            }
                        }
                        int targetPos = targetCol + targetRow * 16;
                        if(compPos <= targetPos+16){
                            (new ControllerMoveRobot(board))->control(id, targetPos+16);
                        }else{
                            (new ControllerMoveRobot(board))->control(id, compPos);
                        }
                        click = 0;
                        emit movementOccurred();
                        return;
                    }
                    click = 0;
                }
            }else{
                clearSelectionSquares();
                click = 0;
            }
        }
    }


    update();

}

void viewPlateau::drawSelectionSquare(int row, int col, int id)
{
    int x = col * CellSize;
    int y = row * CellSize;

    QGraphicsRectItem* selectionSquare = new QGraphicsRectItem(x, y, CellSize, CellSize);

    int r=0;
    int g=0;
    int b=0;

    switch(id){
    case 0:
        r=255;
        break;
    case 1:
        g=255;
        break;
    case 2:
        b=255;
        break;
    case 3:
        g=255;
        r=255;
        break;
    }

    QBrush brush(QColor(r, g, b, 128));
    selectionSquare->setBrush(brush);
    addItem(selectionSquare);

    selectionSquares.push_back(selectionSquare);
}

void viewPlateau::clearSelectionSquares()
{
    for (QGraphicsRectItem* square : selectionSquares) {
        removeItem(square);
        delete square;
    }

    selectionSquares.clear();
}

