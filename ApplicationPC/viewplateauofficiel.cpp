#include "viewplateauofficiel.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
using namespace std;
#include <iostream>

inline bool operator<(const QPointF& p1, const QPointF& p2) {
    return p1.x() < p2.x() || (p1.x() == p2.x() && p1.y() < p2.y());
}

ViewPlateauOfficiel::ViewPlateauOfficiel(Board* board) : QGraphicsScene(), Observer(), it(imagePositions.end()) {
    this->board=board;
    board->addObserver(this);

    (new ControllerReset(board))->control();

    imagePositions = std::map<QPointF, QString, std::function<bool(const QPointF&, const QPointF&)>>([&](const QPointF& p1, const QPointF& p2) {
        if (p1.x() < p2.x()) return true;
        if (p1.x() > p2.x()) return false;
        return p1.y() < p2.y();
    });


    imagePositions[QPointF(95, 70)] = ":/img/Img/part1.jpg";
    imagePositions[QPointF(190, 70)] = ":/img/Img/part2.jpg";
    imagePositions[QPointF(285, 70)] = ":/img/Img/part3.jpg";
    imagePositions[QPointF(380, 70)] = ":/img/Img/part4.jpg";
    imagePositions[QPointF(95, 165)] = ":/img/Img/part5.jpg";
    imagePositions[QPointF(190, 165)] = ":/img/Img/part6.jpg";
    imagePositions[QPointF(285, 165)] = ":/img/Img/part7.jpg";
    imagePositions[QPointF(380, 165)] = ":/img/Img/part8.jpg";
    imagePositions[QPointF(95, 260)] = ":/img/Img/part9.jpg";
    imagePositions[QPointF(190, 260)] = ":/img/Img/part10.jpg";
    imagePositions[QPointF(285, 260)] = ":/img/Img/part11.jpg";
    imagePositions[QPointF(380, 260)] = ":/img/Img/part12.jpg";
    imagePositions[QPointF(95, 355)] = ":/img/Img/part13.jpg";
    imagePositions[QPointF(190, 355)] = ":/img/Img/part14.jpg";
    imagePositions[QPointF(285, 355)] = ":/img/Img/part15.jpg";
    imagePositions[QPointF(380, 355)] = ":/img/Img/part16.jpg";

    updateModel();
}

void ViewPlateauOfficiel::updateModel(){
    setSceneRect(0, 0, 1000, 420);
}

void ViewPlateauOfficiel::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        QPointF mousePos = mouseEvent->scenePos();

        if(click==0){
            it = imagePositions.end();
        }

        if(click==0){
            it = std::find_if(imagePositions.begin(), imagePositions.end(), [&](const auto& pair) {
                const QPointF& position = pair.first;
                return mousePos.x() >= position.x() - 30 &&
                        mousePos.x() <= position.x() + 30 &&
                        mousePos.y() >= position.y() - 30 &&
                        mousePos.y() <= position.y() + 30;
            });
        }

        if (it != imagePositions.end()) {
            if (it == imagePositions.begin() ||
                    std::next(imagePositions.begin(), 1) == it ||
                    std::next(imagePositions.begin(), 2) == it ||
                    std::next(imagePositions.begin(), 3) == it) {
                col=1;
            }else if (it == std::next(imagePositions.begin(), 4) ||
                      it == std::next(imagePositions.begin(), 5) ||
                      it == std::next(imagePositions.begin(), 6) ||
                      it == std::next(imagePositions.begin(), 7)) {
                col=2;
            }else if (it == std::next(imagePositions.begin(), 8) ||
                      it == std::next(imagePositions.begin(), 9) ||
                      it == std::next(imagePositions.begin(), 10) ||
                      it == std::next(imagePositions.begin(), 11)) {
                col=3;
            }else if (it == std::next(imagePositions.begin(), 12) ||
                      it == std::next(imagePositions.begin(), 13) ||
                      it == std::next(imagePositions.begin(), 14) ||
                      it == std::next(imagePositions.begin(), 15)) {
                col=4;
            }



            secondClickPos = mousePos;
            click++;
        }

        if(click==2){
            if (it != imagePositions.end()) {
                QPixmap pixmap(it->second);
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
                if(secondClickPos.x()<730 && secondClickPos.y()<210 && secondClickPos.y()>10 && secondClickPos.x()>530){
                    //deleteTopLeft(this->board);
                    item->setScale(0.65);
                    QPointF origin = item->transformOriginPoint();
                    item->setTransformOriginPoint(item->boundingRect().center());

                    if(col==1){
                        item->setRotation(0);
                        item->setTransformOriginPoint(origin);
                        item->setPos(533,15);
                    }else if(col==2){
                        item->setRotation(90);
                        item->setTransformOriginPoint(origin);
                        item->setPos(728,15);
                    }else if(col==3){
                        item->setRotation(270);
                        item->setTransformOriginPoint(origin);
                        item->setPos(533,210);
                    }else if(col==4){
                        item->setRotation(180);
                        item->setTransformOriginPoint(origin);
                        item->setPos(728,210);
                    }

                    position = 0;
                    addItem(item);
                }else if(secondClickPos.x()<930 && secondClickPos.y()<210 && secondClickPos.y()>10 && secondClickPos.x()>730){
                    //deleteTopRight(this->board);
                    item->setScale(0.65);
                    QPointF origin = item->transformOriginPoint();
                    item->setTransformOriginPoint(item->boundingRect().center());

                    if(col==1){
                        item->setRotation(90);
                        item->setTransformOriginPoint(origin);
                        item->setPos(925,15);
                    }else if(col==2){
                        item->setRotation(180);
                        item->setTransformOriginPoint(origin);
                        item->setPos(925,210);
                    }else if(col==3){
                        item->setRotation(0);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,15);
                    }else if(col==4){
                        item->setRotation(270);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,210);
                    }
                    addItem(item);
                    position = 1;
                }else if(secondClickPos.x()<730 && secondClickPos.y()<410 && secondClickPos.y()>210 && secondClickPos.x()>530){
                    //deleteBotLeft(this->board);
                    item->setScale(0.65);
                    QPointF origin = item->transformOriginPoint();
                    item->setTransformOriginPoint(item->boundingRect().center());

                    if(col==1){
                        item->setRotation(270);
                        item->setTransformOriginPoint(origin);
                        item->setPos(533,407);
                    }else if(col==2){
                        item->setRotation(0);
                        item->setTransformOriginPoint(origin);
                        item->setPos(533,212);
                    }else if(col==3){
                        item->setRotation(180);
                        item->setTransformOriginPoint(origin);
                        item->setPos(728,407);
                    }else if(col==4){
                        item->setRotation(90);
                        item->setTransformOriginPoint(origin);
                        item->setPos(728,212);
                    }
                    addItem(item);
                    position = 2;
                }else if(secondClickPos.x()<930 && secondClickPos.y()<410 && secondClickPos.y()>210 && secondClickPos.x()>730){
                    //deleteBotRight(this->board);
                    item->setScale(0.65);
                    QPointF origin = item->transformOriginPoint();
                    item->setTransformOriginPoint(item->boundingRect().center());

                    if(col==1){
                        item->setRotation(180);
                        item->setTransformOriginPoint(origin);
                        item->setPos(925,407);
                    }else if(col==2){
                        item->setRotation(270);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,407);
                    }else if(col==3){
                        item->setRotation(90);
                        item->setTransformOriginPoint(origin);
                        item->setPos(925,212);
                    }else if(col==4){
                        item->setRotation(0);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,212);
                    }
                    addItem(item);
                    position = 3;
                }

                switch (std::distance(imagePositions.begin(), it)) {
                case 0:
                    board->constructPart1(this->board, position);
                    break;
                case 1:
                    board->constructPart5(this->board, position);
                    break;
                case 2:
                    board->constructPart9(this->board, position);
                    break;
                case 3:
                    board->constructPart13(this->board, position);
                    break;
                case 4:
                    board->constructPart2(this->board, position);
                    break;
                case 5:
                    board->constructPart6(this->board, position);
                    break;
                case 6:
                    board->constructPart10(this->board, position);
                    break;
                case 7:
                    board->constructPart14(this->board, position);
                    break;
                case 8:
                    board->constructPart3(this->board, position);
                    break;
                case 9:
                    board->constructPart7(this->board, position);
                    break;
                case 10:
                    board->constructPart11(this->board, position);
                    break;
                case 11:
                    board->constructPart15(this->board, position);
                    break;
                case 12:
                    board->constructPart4(this->board, position);
                    break;
                case 13:
                    board->constructPart8(this->board, position);
                    break;
                case 14:
                    board->constructPart12(this->board, position);
                    break;
                case 15:
                    board->constructPart16(this->board, position);
                    break;
                }


            }
            click++;
        }
        if(click==3){
            click=0;
        }
    }
}

void ViewPlateauOfficiel::deleteTopLeft(Board *board){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            int cas = j + (i * 16);
            (new ControllerRemoveObj(board))->control(cas);
            (new ControllerRemoveWall(board))->control(cas);
            std::cout<<cas<<std::endl;
        }
    }
}

void ViewPlateauOfficiel::deleteTopRight(Board *board){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            int cas = (j + (i * 16))+8;
            (new ControllerRemoveObj(board))->control(cas);
            (new ControllerRemoveWall(board))->control(cas);
            std::cout<<cas<<std::endl;
        }
    }
}

void ViewPlateauOfficiel::deleteBotLeft(Board *board){
    for(int i=8;i<16;i++){
        for(int j=0;j<8;j++){
            int cas = j + (i * 16);
            (new ControllerRemoveObj(board))->control(cas);
            (new ControllerRemoveWall(board))->control(cas);
            std::cout<<cas<<std::endl;
        }
    }
}

void ViewPlateauOfficiel::deleteBotRight(Board *board){
    for(int i=8;i<16;i++){
        for(int j=0;j<8;j++){
            int cas = (j + (i * 16))+8;
            (new ControllerRemoveObj(board))->control(cas);
            (new ControllerRemoveWall(board))->control(cas);
            std::cout<<cas<<std::endl;
        }
    }
}
