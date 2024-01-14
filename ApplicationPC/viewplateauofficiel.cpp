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

    imagePositions = std::map<QPointF, QString, std::function<bool(const QPointF&, const QPointF&)>>([&](const QPointF& p1, const QPointF& p2) {
        if (p1.x() < p2.x()) return true;
        if (p1.x() > p2.x()) return false;
        return p1.y() < p2.y();
    });


    imagePositions[QPointF(95, 70)] = ":/img/part1.jpg";
    imagePositions[QPointF(190, 70)] = ":/img/part2.jpg";
    imagePositions[QPointF(285, 70)] = ":/img/part3.jpg";
    imagePositions[QPointF(380, 70)] = ":/img/part4.jpg";
    imagePositions[QPointF(95, 165)] = ":/img/part5.jpg";
    imagePositions[QPointF(190, 165)] = ":/img/part6.jpg";
    imagePositions[QPointF(285, 165)] = ":/img/part7.jpg";
    imagePositions[QPointF(380, 165)] = ":/img/part8.jpg";
    imagePositions[QPointF(95, 260)] = ":/img/part9.jpg";
    imagePositions[QPointF(190, 260)] = ":/img/part10.jpg";
    imagePositions[QPointF(285, 260)] = ":/img/part11.jpg";
    imagePositions[QPointF(380, 260)] = ":/img/part12.jpg";
    imagePositions[QPointF(95, 355)] = ":/img/part13.jpg";
    imagePositions[QPointF(190, 355)] = ":/img/part14.jpg";
    imagePositions[QPointF(285, 355)] = ":/img/part15.jpg";
    imagePositions[QPointF(380, 355)] = ":/img/part16.jpg";

    updateModel();
}

void ViewPlateauOfficiel::updateModel(){
    setSceneRect(0, 0, 1000, 420);
}

void ViewPlateauOfficiel::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        QPointF mousePos = mouseEvent->scenePos();
        std::cout << "x" << mousePos.x() << std::endl;
        std::cout << "y" << mousePos.y() << std::endl;

        if(click==0){
            it = imagePositions.end();
        }

        cout<<click<<endl;

        if(click==0){
            it = std::find_if(imagePositions.begin(), imagePositions.end(), [&](const auto& pair) {
                const QPointF& position = pair.first;
                return mousePos.x() >= position.x() - 30 &&
                        mousePos.x() <= position.x() + 30 &&
                        mousePos.y() >= position.y() - 30 &&
                        mousePos.y() <= position.y() + 30;
            });
        }

        cout<<click<<endl;

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

        cout<<"col" << col<<endl;

        if(click==2){
            if (it != imagePositions.end()) {
                std::cout << "Image should appear" << std::endl;
                QPixmap pixmap(it->second);
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
                if(secondClickPos.x()<730 && secondClickPos.y()<210 && secondClickPos.y()>10 && secondClickPos.x()>530){
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

                    //                    if(it == imagePositions.begin()){
                    //                        constructPart1(this->board,0);
                    //                    }else if(std::next(imagePositions.begin(), 1) == it){
                    //                        constructPart5(this->board,0);
                    //                    }else if(std::next(imagePositions.begin(), 2) == it){
                    //                        constructPart9(this->board,0);
                    //                    }else if(std::next(imagePositions.begin(), 3) == it){
                    //                        constructPart13(this->board,0);
                    //                    }
                    //                    else if(std::next(imagePositions.begin(), 3) == it){
                    //                        constructPart13(this->board,0);
                    //                    }else if(std::next(imagePositions.begin(), 3) == it){
                    //                        constructPart13(this->board,0);
                    //                    }else if(std::next(imagePositions.begin(), 3) == it){
                    //                        constructPart13(this->board,0);
                    //                    }else if(std::next(imagePositions.begin(), 3) == it){
                    //                        constructPart13(this->board,0);
                    //                    }else if(std::next(imagePositions.begin(), 3) == it){
                    //                        constructPart13(this->board,0);
                    //                    }
                    addItem(item);
                }else if(secondClickPos.x()<930 && secondClickPos.y()<210 && secondClickPos.y()>10 && secondClickPos.x()>730){
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
                    constructPart1(this->board, position);
                    break;
                case 1:
                    constructPart5(this->board, position);
                    break;
                case 2:
                    constructPart9(this->board, position);
                    break;
                case 3:
                    constructPart13(this->board, position);
                    break;
                case 4:
                    constructPart2(this->board, position);
                    break;
                case 5:
                    constructPart6(this->board, position);
                    break;
                case 6:
                    constructPart10(this->board, position);
                    break;
                case 7:
                    constructPart14(this->board, position);
                    break;
                case 8:
                    constructPart3(this->board, position);
                    break;
                case 9:
                    constructPart7(this->board, position);
                    break;
                case 10:
                    constructPart11(this->board, position);
                    break;
                case 11:
                    constructPart15(this->board, position);
                    break;
                case 12:
                    constructPart4(this->board, position);
                    break;
                case 13:
                    constructPart8(this->board, position);
                    break;
                case 14:
                    constructPart12(this->board, position);
                    break;
                case 15:
                    constructPart16(this->board, position);
                    break;
                }


            }
            click++;
        }
        cout<<click<<endl;
        if(click==3){
            click=0;
        }
    }
}



int ViewPlateauOfficiel::posToId(int x, int y) {
    return x + y * 16;
}



void ViewPlateauOfficiel::constructPart1(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[13] = posToId(6, 1);
        board->objectives[3] = posToId(4, 3);
        board->objectives[8] = posToId(1, 5);
        board->objectives[6] = posToId(5, 6);
        board->objectives[16] = posToId(2, 7);

        SET_WALL(board->cases[posToId(3, 0)], EAST);
        SET_WALL(board->cases[posToId(4, 0)], WEST);
        SET_WALL(board->cases[posToId(5, 1)], EAST);
        SET_WALL(board->cases[posToId(6, 1)], WEST);
        SET_WALL(board->cases[posToId(6, 1)], SOUTH);
        SET_WALL(board->cases[posToId(0, 2)], SOUTH);
        SET_WALL(board->cases[posToId(6, 2)], NORTH);
        SET_WALL(board->cases[posToId(0, 3)], NORTH);
        SET_WALL(board->cases[posToId(4, 3)], EAST);
        SET_WALL(board->cases[posToId(5, 3)], WEST);
        SET_WALL(board->cases[posToId(4, 3)], SOUTH);
        SET_WALL(board->cases[posToId(1, 4)], SOUTH);
        SET_WALL(board->cases[posToId(4, 4)], NORTH);
        SET_WALL(board->cases[posToId(1, 5)], NORTH);
        SET_WALL(board->cases[posToId(1, 5)], EAST);
        SET_WALL(board->cases[posToId(2, 5)], WEST);
        SET_WALL(board->cases[posToId(5, 5)], SOUTH);
        SET_WALL(board->cases[posToId(4, 6)], EAST);
        SET_WALL(board->cases[posToId(5, 6)], WEST);
        SET_WALL(board->cases[posToId(5, 6)], NORTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(2, 7)], SOUTH);
        SET_WALL(board->cases[posToId(2, 7)], EAST);
        SET_WALL(board->cases[posToId(3, 7)], WEST);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[13] = posToId(14, 6);
        board->objectives[3] = posToId(12, 4);
        board->objectives[8] = posToId(10, 1);
        board->objectives[6] = posToId(9, 5);
        board->objectives[16] = posToId(8, 2);

        SET_WALL(board->cases[posToId(12, 0)], EAST);
        SET_WALL(board->cases[posToId(13, 0)], WEST);
        SET_WALL(board->cases[posToId(10, 1)], EAST);
        SET_WALL(board->cases[posToId(10, 1)], SOUTH);
        SET_WALL(board->cases[posToId(11, 1)], WEST);
        SET_WALL(board->cases[posToId(8, 2)], WEST);
        SET_WALL(board->cases[posToId(8, 2)], SOUTH);
        SET_WALL(board->cases[posToId(10, 2)], NORTH);
        SET_WALL(board->cases[posToId(8, 3)], NORTH);
        SET_WALL(board->cases[posToId(15, 3)], SOUTH);
        SET_WALL(board->cases[posToId(9, 4)], SOUTH);
        SET_WALL(board->cases[posToId(11, 4)], EAST);
        SET_WALL(board->cases[posToId(12, 4)], SOUTH);
        SET_WALL(board->cases[posToId(12, 4)], WEST);
        SET_WALL(board->cases[posToId(15, 4)], NORTH);
        SET_WALL(board->cases[posToId(9, 5)], NORTH);
        SET_WALL(board->cases[posToId(9, 5)], EAST);
        SET_WALL(board->cases[posToId(10, 5)], WEST);
        SET_WALL(board->cases[posToId(12, 5)], NORTH);
        SET_WALL(board->cases[posToId(14, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(13, 6)], EAST);
        SET_WALL(board->cases[posToId(14, 6)], WEST);
        SET_WALL(board->cases[posToId(14, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);

        return;
    }

    if (pos == 2) {
        board->objectives[13] = posToId(2, 9);
        board->objectives[3] = posToId(3, 11);
        board->objectives[8] = posToId(5, 14);
        board->objectives[6] = posToId(6, 10);
        board->objectives[16] = posToId(13, 2);

        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(1, 9)], SOUTH);
        SET_WALL(board->cases[posToId(1, 9)], EAST);
        SET_WALL(board->cases[posToId(2, 9)], WEST);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(1, 10)], NORTH);
        SET_WALL(board->cases[posToId(3, 10)], SOUTH);
        SET_WALL(board->cases[posToId(5, 10)], EAST);
        SET_WALL(board->cases[posToId(6, 10)], WEST);
        SET_WALL(board->cases[posToId(6, 10)], SOUTH);
        SET_WALL(board->cases[posToId(0, 11)], SOUTH);
        SET_WALL(board->cases[posToId(3, 11)], NORTH);
        SET_WALL(board->cases[posToId(3, 11)], EAST);
        SET_WALL(board->cases[posToId(4, 11)], WEST);
        SET_WALL(board->cases[posToId(6, 11)], NORTH);
        SET_WALL(board->cases[posToId(0, 12)], NORTH);
        SET_WALL(board->cases[posToId(7, 12)], SOUTH);
        SET_WALL(board->cases[posToId(5, 13)], SOUTH);
        SET_WALL(board->cases[posToId(7, 13)], NORTH);
        SET_WALL(board->cases[posToId(7, 13)], EAST);
        SET_WALL(board->cases[posToId(4, 14)], EAST);
        SET_WALL(board->cases[posToId(5, 14)], WEST);
        SET_WALL(board->cases[posToId(5, 14)], NORTH);
        SET_WALL(board->cases[posToId(2, 15)], EAST);
        SET_WALL(board->cases[posToId(3, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[13] = posToId(9, 15);
        board->objectives[3] = posToId(11, 12);
        board->objectives[8] = posToId(14, 10);
        board->objectives[6] = posToId(10, 9);
        board->objectives[16] = posToId(13, 8);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(12, 8)], EAST);
        SET_WALL(board->cases[posToId(13, 8)], WEST);
        SET_WALL(board->cases[posToId(13, 8)], NORTH);
        SET_WALL(board->cases[posToId(8, 9)], SOUTH);
        SET_WALL(board->cases[posToId(10, 9)], EAST);
        SET_WALL(board->cases[posToId(10, 9)], SOUTH);
        SET_WALL(board->cases[posToId(11, 9)], WEST);
        SET_WALL(board->cases[posToId(10, 10)], NORTH);
        SET_WALL(board->cases[posToId(13, 10)], EAST);
        SET_WALL(board->cases[posToId(14, 10)], WEST);
        SET_WALL(board->cases[posToId(14, 10)], SOUTH);
        SET_WALL(board->cases[posToId(11, 11)], SOUTH);
        SET_WALL(board->cases[posToId(14, 11)], NORTH);
        SET_WALL(board->cases[posToId(10, 12)], EAST);
        SET_WALL(board->cases[posToId(11, 12)], WEST);
        SET_WALL(board->cases[posToId(11, 12)], NORTH);
        SET_WALL(board->cases[posToId(15, 12)], SOUTH);
        SET_WALL(board->cases[posToId(9, 13)], SOUTH);
        SET_WALL(board->cases[posToId(15, 13)], NORTH);
        SET_WALL(board->cases[posToId(9, 14)], NORTH);
        SET_WALL(board->cases[posToId(9, 14)], EAST);
        SET_WALL(board->cases[posToId(10, 14)], WEST);
        SET_WALL(board->cases[posToId(11, 15)], EAST);
        SET_WALL(board->cases[posToId(12, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart2(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[2] = posToId(2, 1);
        board->objectives[9] = posToId(6, 2);
        board->objectives[7] = posToId(1, 5);
        board->objectives[12] = posToId(4, 6);

        SET_WALL(board->cases[posToId(2, 0)], SOUTH);
        SET_WALL(board->cases[posToId(3, 0)], EAST);
        SET_WALL(board->cases[posToId(4, 0)], WEST);
        SET_WALL(board->cases[posToId(2, 1)], NORTH);
        SET_WALL(board->cases[posToId(2, 1)], EAST);
        SET_WALL(board->cases[posToId(3, 1)], WEST);
        SET_WALL(board->cases[posToId(5, 2)], EAST);
        SET_WALL(board->cases[posToId(6, 2)], WEST);
        SET_WALL(board->cases[posToId(6, 2)], SOUTH);
        SET_WALL(board->cases[posToId(0, 3)], SOUTH);
        SET_WALL(board->cases[posToId(0, 4)], NORTH);
        SET_WALL(board->cases[posToId(1, 5)], SOUTH);
        SET_WALL(board->cases[posToId(1, 5)], EAST);
        SET_WALL(board->cases[posToId(2, 5)], WEST);
        SET_WALL(board->cases[posToId(4, 5)], SOUTH);
        SET_WALL(board->cases[posToId(1, 6)], NORTH);
        SET_WALL(board->cases[posToId(3, 6)], EAST);
        SET_WALL(board->cases[posToId(4, 6)], WEST);
        SET_WALL(board->cases[posToId(4, 6)], NORTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[2] = posToId(14, 2);
        board->objectives[9] = posToId(13, 6);
        board->objectives[7] = posToId(10, 1);
        board->objectives[12] = posToId(9, 4);

        SET_WALL(board->cases[posToId(11, 0)], WEST);
        SET_WALL(board->cases[posToId(12, 0)], EAST);
        SET_WALL(board->cases[posToId(9, 1)], EAST);
        SET_WALL(board->cases[posToId(10, 1)], WEST);
        SET_WALL(board->cases[posToId(10, 1)], SOUTH);
        SET_WALL(board->cases[posToId(10, 2)], NORTH);
        SET_WALL(board->cases[posToId(14, 2)], SOUTH);
        SET_WALL(board->cases[posToId(14, 2)], EAST);
        SET_WALL(board->cases[posToId(15, 2)], WEST);
        SET_WALL(board->cases[posToId(10, 3)], SOUTH);
        SET_WALL(board->cases[posToId(15, 3)], SOUTH);
        SET_WALL(board->cases[posToId(10, 4)], NORTH);
        SET_WALL(board->cases[posToId(10, 4)], EAST);
        SET_WALL(board->cases[posToId(11, 4)], WEST);
        SET_WALL(board->cases[posToId(15, 4)], NORTH);
        SET_WALL(board->cases[posToId(13, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(12, 6)], EAST);
        SET_WALL(board->cases[posToId(13, 6)], WEST);
        SET_WALL(board->cases[posToId(13, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);

        return;
    }

    if (pos == 2) {
        board->objectives[2] = posToId(1, 13);
        board->objectives[9] = posToId(2, 9);
        board->objectives[7] = posToId(10, 1);
        board->objectives[12] = posToId(5, 14);

        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(2, 9)], SOUTH);
        SET_WALL(board->cases[posToId(2, 9)], EAST);
        SET_WALL(board->cases[posToId(3, 9)], WEST);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(2, 10)], NORTH);
        SET_WALL(board->cases[posToId(0, 11)], SOUTH);
        SET_WALL(board->cases[posToId(5, 11)], EAST);
        SET_WALL(board->cases[posToId(6, 11)], WEST);
        SET_WALL(board->cases[posToId(6, 11)], SOUTH);
        SET_WALL(board->cases[posToId(0, 12)], NORTH);
        SET_WALL(board->cases[posToId(1, 12)], SOUTH);
        SET_WALL(board->cases[posToId(6, 12)], NORTH);
        SET_WALL(board->cases[posToId(0, 13)], EAST);
        SET_WALL(board->cases[posToId(1, 13)], WEST);
        SET_WALL(board->cases[posToId(1, 13)], NORTH);
        SET_WALL(board->cases[posToId(5, 13)], SOUTH);
        SET_WALL(board->cases[posToId(5, 14)], NORTH);
        SET_WALL(board->cases[posToId(5, 14)], EAST);
        SET_WALL(board->cases[posToId(6, 14)], WEST);
        SET_WALL(board->cases[posToId(3, 15)], EAST);
        SET_WALL(board->cases[posToId(4, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[2] = posToId(13, 14);
        board->objectives[9] = posToId(9, 13);
        board->objectives[7] = posToId(14, 10);
        board->objectives[12] = posToId(11, 9);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(11, 9)], SOUTH);
        SET_WALL(board->cases[posToId(11, 9)], EAST);
        SET_WALL(board->cases[posToId(12, 9)], WEST);
        SET_WALL(board->cases[posToId(14, 9)], SOUTH);
        SET_WALL(board->cases[posToId(11, 10)], NORTH);
        SET_WALL(board->cases[posToId(13, 10)], EAST);
        SET_WALL(board->cases[posToId(14, 10)], WEST);
        SET_WALL(board->cases[posToId(14, 10)], NORTH);
        SET_WALL(board->cases[posToId(15, 11)], SOUTH);
        SET_WALL(board->cases[posToId(9, 12)], SOUTH);
        SET_WALL(board->cases[posToId(15, 12)], NORTH);
        SET_WALL(board->cases[posToId(9, 13)], NORTH);
        SET_WALL(board->cases[posToId(9, 13)], EAST);
        SET_WALL(board->cases[posToId(10, 13)], WEST);
        SET_WALL(board->cases[posToId(12, 14)], EAST);
        SET_WALL(board->cases[posToId(13, 14)], WEST);
        SET_WALL(board->cases[posToId(13, 14)], SOUTH);
        SET_WALL(board->cases[posToId(11, 15)], EAST);
        SET_WALL(board->cases[posToId(12, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart3(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[13] = posToId(3, 1);
        board->objectives[3] = posToId(5, 2);
        board->objectives[6] = posToId(4, 5);
        board->objectives[8] = posToId(1, 6);
        board->objectives[16] = posToId(5, 7);

        SET_WALL(board->cases[posToId(6, 0)], EAST);
        SET_WALL(board->cases[posToId(7, 0)], WEST);
        SET_WALL(board->cases[posToId(2, 1)], EAST);
        SET_WALL(board->cases[posToId(3, 1)], WEST);
        SET_WALL(board->cases[posToId(3, 1)], SOUTH);
        SET_WALL(board->cases[posToId(5, 2)], SOUTH);
        SET_WALL(board->cases[posToId(5, 2)], EAST);
        SET_WALL(board->cases[posToId(6, 2)], WEST);
        SET_WALL(board->cases[posToId(0, 3)], SOUTH);
        SET_WALL(board->cases[posToId(0, 4)], NORTH);
        SET_WALL(board->cases[posToId(4, 4)], SOUTH);
        SET_WALL(board->cases[posToId(1, 5)], SOUTH);
        SET_WALL(board->cases[posToId(3, 5)], EAST);
        SET_WALL(board->cases[posToId(4, 5)], WEST);
        SET_WALL(board->cases[posToId(4, 5)], NORTH);
        SET_WALL(board->cases[posToId(1, 6)], NORTH);
        SET_WALL(board->cases[posToId(1, 6)], EAST);
        SET_WALL(board->cases[posToId(2, 6)], WEST);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(5, 7)], SOUTH);
        SET_WALL(board->cases[posToId(5, 7)], EAST);
        SET_WALL(board->cases[posToId(6, 7)], WEST);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[13] = posToId(6, 3);
        board->objectives[3] = posToId(14, 13);
        board->objectives[6] = posToId(10, 4);
        board->objectives[8] = posToId(9, 1);
        board->objectives[16] = posToId(8, 13);

        SET_WALL(board->cases[posToId(11, 0)], EAST);
        SET_WALL(board->cases[posToId(12, 0)], WEST);
        SET_WALL(board->cases[posToId(9, 1)], SOUTH);
        SET_WALL(board->cases[posToId(9, 1)], EAST);
        SET_WALL(board->cases[posToId(10, 1)], WEST);
        SET_WALL(board->cases[posToId(9, 2)], NORTH);
        SET_WALL(board->cases[posToId(14, 2)], SOUTH);
        SET_WALL(board->cases[posToId(11, 3)], SOUTH);
        SET_WALL(board->cases[posToId(14, 3)], EAST);
        SET_WALL(board->cases[posToId(15, 3)], WEST);
        SET_WALL(board->cases[posToId(15, 3)], NORTH);
        SET_WALL(board->cases[posToId(10, 4)], NORTH);
        SET_WALL(board->cases[posToId(10, 4)], EAST);
        SET_WALL(board->cases[posToId(11, 4)], WEST);
        SET_WALL(board->cases[posToId(8, 5)], WEST);
        SET_WALL(board->cases[posToId(8, 5)], SOUTH);
        SET_WALL(board->cases[posToId(12, 5)], EAST);
        SET_WALL(board->cases[posToId(13, 5)], WEST);
        SET_WALL(board->cases[posToId(13, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], NORTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(15, 6)], SOUTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(15, 7)], NORTH);

        return;
    }

    if (pos == 2) {
        board->objectives[13] = posToId(1, 12);
        board->objectives[3] = posToId(2, 10);
        board->objectives[6] = posToId(5, 11);
        board->objectives[8] = posToId(6, 14);
        board->objectives[16] = posToId(7, 10);

        SET_WALL(board->cases[posToId(0, 8)], SOUTH);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], NORTH);
        SET_WALL(board->cases[posToId(2, 9)], SOUTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(7, 9)], SOUTH);
        SET_WALL(board->cases[posToId(2, 10)], NORTH);
        SET_WALL(board->cases[posToId(2, 10)], EAST);
        SET_WALL(board->cases[posToId(3, 10)], WEST);
        SET_WALL(board->cases[posToId(7, 10)], NORTH);
        SET_WALL(board->cases[posToId(7, 10)], EAST);
        SET_WALL(board->cases[posToId(4, 11)], EAST);
        SET_WALL(board->cases[posToId(5, 11)], WEST);
        SET_WALL(board->cases[posToId(5, 11)], SOUTH);
        SET_WALL(board->cases[posToId(1, 12)], SOUTH);
        SET_WALL(board->cases[posToId(1, 12)], EAST);
        SET_WALL(board->cases[posToId(2, 12)], WEST);
        SET_WALL(board->cases[posToId(5, 12)], NORTH);
        SET_WALL(board->cases[posToId(1, 13)], NORTH);
        SET_WALL(board->cases[posToId(6, 13)], SOUTH);
        SET_WALL(board->cases[posToId(5, 14)], EAST);
        SET_WALL(board->cases[posToId(6, 14)], WEST);
        SET_WALL(board->cases[posToId(6, 14)], NORTH);
        SET_WALL(board->cases[posToId(3, 15)], EAST);
        SET_WALL(board->cases[posToId(4, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[13] = posToId(12, 14);
        board->objectives[3] = posToId(10, 13);
        board->objectives[6] = posToId(11, 10);
        board->objectives[8] = posToId(14, 9);
        board->objectives[16] = posToId(10, 8);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(9, 8)], EAST);
        SET_WALL(board->cases[posToId(10, 8)], WEST);
        SET_WALL(board->cases[posToId(10, 8)], NORTH);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(13, 9)], EAST);
        SET_WALL(board->cases[posToId(14, 9)], WEST);
        SET_WALL(board->cases[posToId(14, 9)], SOUTH);
        SET_WALL(board->cases[posToId(11, 10)], SOUTH);
        SET_WALL(board->cases[posToId(11, 10)], EAST);
        SET_WALL(board->cases[posToId(12, 10)], WEST);
        SET_WALL(board->cases[posToId(14, 10)], NORTH);
        SET_WALL(board->cases[posToId(11, 11)], NORTH);
        SET_WALL(board->cases[posToId(15, 11)], SOUTH);
        SET_WALL(board->cases[posToId(10, 12)], SOUTH);
        SET_WALL(board->cases[posToId(15, 12)], NORTH);
        SET_WALL(board->cases[posToId(9, 13)], EAST);
        SET_WALL(board->cases[posToId(10, 13)], WEST);
        SET_WALL(board->cases[posToId(10, 13)], NORTH);
        SET_WALL(board->cases[posToId(12, 13)], SOUTH);
        SET_WALL(board->cases[posToId(12, 14)], NORTH);
        SET_WALL(board->cases[posToId(12, 14)], EAST);
        SET_WALL(board->cases[posToId(13, 14)], WEST);
        SET_WALL(board->cases[posToId(8, 15)], EAST);
        SET_WALL(board->cases[posToId(9, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart4(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[1] = posToId(1, 1);
        board->objectives[11] = posToId(4, 2);
        board->objectives[4] = posToId(2, 6);
        board->objectives[14] = posToId(5, 7);

        SET_WALL(board->cases[posToId(1, 0)], SOUTH);
        SET_WALL(board->cases[posToId(5, 0)], EAST);
        SET_WALL(board->cases[posToId(6, 0)], WEST);
        SET_WALL(board->cases[posToId(1, 1)], NORTH);
        SET_WALL(board->cases[posToId(1, 1)], EAST);
        SET_WALL(board->cases[posToId(6, 1)], WEST);
        SET_WALL(board->cases[posToId(4, 2)], SOUTH);
        SET_WALL(board->cases[posToId(4, 2)], EAST);
        SET_WALL(board->cases[posToId(5, 2)], WEST);
        SET_WALL(board->cases[posToId(0, 3)], SOUTH);
        SET_WALL(board->cases[posToId(4, 3)], NORTH);
        SET_WALL(board->cases[posToId(0, 4)], NORTH);
        SET_WALL(board->cases[posToId(1, 6)], EAST);
        SET_WALL(board->cases[posToId(2, 6)], WEST);
        SET_WALL(board->cases[posToId(2, 6)], SOUTH);
        SET_WALL(board->cases[posToId(5, 6)], SOUTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(2, 7)], NORTH);
        SET_WALL(board->cases[posToId(4, 7)], EAST);
        SET_WALL(board->cases[posToId(5, 7)], WEST);
        SET_WALL(board->cases[posToId(5, 7)], NORTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[1] = posToId(14, 1);
        board->objectives[11] = posToId(13, 4);
        board->objectives[4] = posToId(9, 2);
        board->objectives[14] = posToId(8, 5);

        SET_WALL(board->cases[posToId(11, 0)], EAST);
        SET_WALL(board->cases[posToId(12, 0)], WEST);
        SET_WALL(board->cases[posToId(9, 1)], SOUTH);
        SET_WALL(board->cases[posToId(14, 1)], SOUTH);
        SET_WALL(board->cases[posToId(14, 1)], EAST);
        SET_WALL(board->cases[posToId(15, 1)], WEST);
        SET_WALL(board->cases[posToId(8, 2)], EAST);
        SET_WALL(board->cases[posToId(9, 2)], WEST);
        SET_WALL(board->cases[posToId(9, 2)], NORTH);
        SET_WALL(board->cases[posToId(14, 2)], NORTH);
        SET_WALL(board->cases[posToId(8, 4)], SOUTH);
        SET_WALL(board->cases[posToId(12, 4)], EAST);
        SET_WALL(board->cases[posToId(13, 4)], WEST);
        SET_WALL(board->cases[posToId(13, 4)], SOUTH);
        SET_WALL(board->cases[posToId(8, 5)], NORTH);
        SET_WALL(board->cases[posToId(8, 5)], EAST);
        SET_WALL(board->cases[posToId(9, 5)], WEST);
        SET_WALL(board->cases[posToId(13, 5)], NORTH);
        SET_WALL(board->cases[posToId(15, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(15, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);

        return;
    }

    if (pos == 2) {
        board->objectives[1] = posToId(1, 15);
        board->objectives[11] = posToId(2, 11);
        board->objectives[4] = posToId(6, 13);
        board->objectives[14] = posToId(7, 10);

        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], SOUTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(0, 10)], NORTH);
        SET_WALL(board->cases[posToId(2, 10)], SOUTH);
        SET_WALL(board->cases[posToId(6, 10)], EAST);
        SET_WALL(board->cases[posToId(7, 10)], WEST);
        SET_WALL(board->cases[posToId(7, 10)], SOUTH);
        SET_WALL(board->cases[posToId(2, 11)], NORTH);
        SET_WALL(board->cases[posToId(2, 11)], EAST);
        SET_WALL(board->cases[posToId(3, 11)], WEST);
        SET_WALL(board->cases[posToId(7, 11)], NORTH);
        SET_WALL(board->cases[posToId(2, 13)], SOUTH);
        SET_WALL(board->cases[posToId(6, 13)], SOUTH);
        SET_WALL(board->cases[posToId(6, 13)], EAST);
        SET_WALL(board->cases[posToId(7, 13)], WEST);
        SET_WALL(board->cases[posToId(0, 14)], EAST);
        SET_WALL(board->cases[posToId(1, 14)], WEST);
        SET_WALL(board->cases[posToId(1, 14)], NORTH);
        SET_WALL(board->cases[posToId(6, 14)], NORTH);
        SET_WALL(board->cases[posToId(3, 15)], EAST);
        SET_WALL(board->cases[posToId(4, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[1] = posToId(14, 14);
        board->objectives[11] = posToId(11, 13);
        board->objectives[4] = posToId(13, 9);
        board->objectives[14] = posToId(10, 8);

        SET_WALL(board->cases[posToId(9, 8)], EAST);
        SET_WALL(board->cases[posToId(10, 8)], EAST);
        SET_WALL(board->cases[posToId(10, 8)], SOUTH);
        SET_WALL(board->cases[posToId(11, 8)], WEST);
        SET_WALL(board->cases[posToId(13, 8)], SOUTH);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(10, 9)], NORTH);
        SET_WALL(board->cases[posToId(13, 9)], NORTH);
        SET_WALL(board->cases[posToId(13, 9)], EAST);
        SET_WALL(board->cases[posToId(14, 9)], WEST);
        SET_WALL(board->cases[posToId(15, 11)], SOUTH);
        SET_WALL(board->cases[posToId(11, 12)], SOUTH);
        SET_WALL(board->cases[posToId(15, 12)], NORTH);
        SET_WALL(board->cases[posToId(10, 13)], EAST);
        SET_WALL(board->cases[posToId(11, 13)], WEST);
        SET_WALL(board->cases[posToId(11, 13)], NORTH);
        SET_WALL(board->cases[posToId(13, 14)], EAST);
        SET_WALL(board->cases[posToId(14, 14)], WEST);
        SET_WALL(board->cases[posToId(14, 14)], SOUTH);
        SET_WALL(board->cases[posToId(9, 15)], EAST);
        SET_WALL(board->cases[posToId(10, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart5(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[3] = posToId(5, 1);
        board->objectives[8] = posToId(3, 2);
        board->objectives[6] = posToId(3, 3);
        board->objectives[16] = posToId(7, 5);
        board->objectives[13] = posToId(2, 6);

        SET_WALL(board->cases[posToId(6, 0)], EAST);
        SET_WALL(board->cases[posToId(7, 0)], WEST);
        SET_WALL(board->cases[posToId(5, 1)], SOUTH);
        SET_WALL(board->cases[posToId(5, 1)], EAST);
        SET_WALL(board->cases[posToId(6, 1)], WEST);
        SET_WALL(board->cases[posToId(2, 2)], EAST);
        SET_WALL(board->cases[posToId(3, 2)], WEST);
        SET_WALL(board->cases[posToId(3, 2)], SOUTH);
        SET_WALL(board->cases[posToId(5, 2)], NORTH);
        SET_WALL(board->cases[posToId(3, 3)], NORTH);
        SET_WALL(board->cases[posToId(3, 3)], EAST);
        SET_WALL(board->cases[posToId(4, 3)], WEST);
        SET_WALL(board->cases[posToId(0, 4)], SOUTH);
        SET_WALL(board->cases[posToId(0, 5)], NORTH);
        SET_WALL(board->cases[posToId(2, 5)], SOUTH);
        SET_WALL(board->cases[posToId(7, 5)], SOUTH);
        SET_WALL(board->cases[posToId(7, 5)], EAST);
        SET_WALL(board->cases[posToId(1, 6)], EAST);
        SET_WALL(board->cases[posToId(2, 6)], WEST);
        SET_WALL(board->cases[posToId(2, 6)], NORTH);
        SET_WALL(board->cases[posToId(7, 6)], NORTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[13] = posToId(9, 2);
        board->objectives[6] = posToId(12, 3);
        board->objectives[8] = posToId(13, 3);
        board->objectives[3] = posToId(14, 5);
        board->objectives[16] = posToId(10, 7);

        SET_WALL(board->cases[posToId(10, 0)], EAST);
        SET_WALL(board->cases[posToId(11, 0)], WEST);
        SET_WALL(board->cases[posToId(9, 1)], SOUTH);
        SET_WALL(board->cases[posToId(9, 2)], NORTH);
        SET_WALL(board->cases[posToId(9, 2)], EAST);
        SET_WALL(board->cases[posToId(10, 2)], WEST);
        SET_WALL(board->cases[posToId(13, 2)], SOUTH);
        SET_WALL(board->cases[posToId(12, 3)], SOUTH);
        SET_WALL(board->cases[posToId(12, 3)], EAST);
        SET_WALL(board->cases[posToId(13, 3)], WEST);
        SET_WALL(board->cases[posToId(13, 3)], NORTH);
        SET_WALL(board->cases[posToId(12, 4)], NORTH);
        SET_WALL(board->cases[posToId(13, 5)], EAST);
        SET_WALL(board->cases[posToId(14, 5)], WEST);
        SET_WALL(board->cases[posToId(14, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(15, 6)], SOUTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(9, 7)], EAST);
        SET_WALL(board->cases[posToId(10, 7)], WEST);
        SET_WALL(board->cases[posToId(10, 7)], SOUTH);
        SET_WALL(board->cases[posToId(15, 7)], NORTH);

        return;
    }

    if (pos == 2) {
        board->objectives[16] = posToId(5, 8);
        board->objectives[3] = posToId(1, 10);
        board->objectives[8] = posToId(2, 12);
        board->objectives[6] = posToId(3, 12);
        board->objectives[13] = posToId(6, 13);

        SET_WALL(board->cases[posToId(0, 8)], SOUTH);
        SET_WALL(board->cases[posToId(5, 8)], NORTH);
        SET_WALL(board->cases[posToId(5, 8)], EAST);
        SET_WALL(board->cases[posToId(6, 8)], WEST);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], NORTH);
        SET_WALL(board->cases[posToId(1, 9)], SOUTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(1, 10)], NORTH);
        SET_WALL(board->cases[posToId(1, 10)], EAST);
        SET_WALL(board->cases[posToId(2, 10)], WEST);
        SET_WALL(board->cases[posToId(3, 11)], SOUTH);
        SET_WALL(board->cases[posToId(2, 12)], SOUTH);
        SET_WALL(board->cases[posToId(2, 12)], EAST);
        SET_WALL(board->cases[posToId(3, 12)], WEST);
        SET_WALL(board->cases[posToId(3, 12)], NORTH);
        SET_WALL(board->cases[posToId(2, 13)], NORTH);
        SET_WALL(board->cases[posToId(5, 13)], EAST);
        SET_WALL(board->cases[posToId(6, 13)], WEST);
        SET_WALL(board->cases[posToId(6, 13)], SOUTH);
        SET_WALL(board->cases[posToId(6, 14)], NORTH);
        SET_WALL(board->cases[posToId(4, 15)], EAST);
        SET_WALL(board->cases[posToId(5, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[13] = posToId(13, 9);
        board->objectives[16] = posToId(8, 10);
        board->objectives[6] = posToId(12, 12);
        board->objectives[8] = posToId(12, 13);
        board->objectives[3] = posToId(10, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(8, 9)], SOUTH);
        SET_WALL(board->cases[posToId(13, 9)], SOUTH);
        SET_WALL(board->cases[posToId(13, 9)], EAST);
        SET_WALL(board->cases[posToId(14, 9)], WEST);
        SET_WALL(board->cases[posToId(8, 10)], NORTH);
        SET_WALL(board->cases[posToId(13, 10)], NORTH);
        SET_WALL(board->cases[posToId(15, 10)], SOUTH);
        SET_WALL(board->cases[posToId(15, 11)], NORTH);
        SET_WALL(board->cases[posToId(11, 12)], EAST);
        SET_WALL(board->cases[posToId(12, 12)], WEST);
        SET_WALL(board->cases[posToId(12, 12)], SOUTH);
        SET_WALL(board->cases[posToId(10, 13)], SOUTH);
        SET_WALL(board->cases[posToId(12, 13)], NORTH);
        SET_WALL(board->cases[posToId(12, 13)], EAST);
        SET_WALL(board->cases[posToId(13, 13)], WEST);
        SET_WALL(board->cases[posToId(9, 14)], EAST);
        SET_WALL(board->cases[posToId(10, 14)], WEST);
        SET_WALL(board->cases[posToId(10, 14)], NORTH);
        SET_WALL(board->cases[posToId(8, 15)], EAST);
        SET_WALL(board->cases[posToId(9, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart6(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[7] = posToId(6, 1);
        board->objectives[12] = posToId(1, 2);
        board->objectives[2] = posToId(5, 4);
        board->objectives[9] = posToId(3, 6);

        SET_WALL(board->cases[posToId(4, 0)], EAST);
        SET_WALL(board->cases[posToId(5, 0)], WEST);
        SET_WALL(board->cases[posToId(1, 1)], SOUTH);
        SET_WALL(board->cases[posToId(6, 1)], SOUTH);
        SET_WALL(board->cases[posToId(6, 1)], EAST);
        SET_WALL(board->cases[posToId(7, 1)], WEST);
        SET_WALL(board->cases[posToId(0, 2)], EAST);
        SET_WALL(board->cases[posToId(1, 2)], WEST);
        SET_WALL(board->cases[posToId(1, 2)], NORTH);
        SET_WALL(board->cases[posToId(6, 2)], NORTH);
        SET_WALL(board->cases[posToId(0, 4)], SOUTH);
        SET_WALL(board->cases[posToId(4, 4)], EAST);
        SET_WALL(board->cases[posToId(5, 4)], WEST);
        SET_WALL(board->cases[posToId(5, 4)], SOUTH);
        SET_WALL(board->cases[posToId(0, 5)], NORTH);
        SET_WALL(board->cases[posToId(3, 5)], SOUTH);
        SET_WALL(board->cases[posToId(5, 5)], NORTH);
        SET_WALL(board->cases[posToId(3, 6)], NORTH);
        SET_WALL(board->cases[posToId(3, 6)], EAST);
        SET_WALL(board->cases[posToId(4, 6)], WEST);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[12] = posToId(13, 1);
        board->objectives[9] = posToId(9, 3);
        board->objectives[2] = posToId(11, 5);
        board->objectives[7] = posToId(14, 6);

        SET_WALL(board->cases[posToId(10, 0)], EAST);
        SET_WALL(board->cases[posToId(11, 0)], WEST);
        SET_WALL(board->cases[posToId(13, 0)], SOUTH);
        SET_WALL(board->cases[posToId(13, 1)], NORTH);
        SET_WALL(board->cases[posToId(13, 1)], EAST);
        SET_WALL(board->cases[posToId(14, 1)], WEST);
        SET_WALL(board->cases[posToId(9, 3)], SOUTH);
        SET_WALL(board->cases[posToId(9, 3)], EAST);
        SET_WALL(board->cases[posToId(10, 3)], WEST);
        SET_WALL(board->cases[posToId(9, 4)], NORTH);
        SET_WALL(board->cases[posToId(11, 4)], SOUTH);
        SET_WALL(board->cases[posToId(15, 4)], SOUTH);
        SET_WALL(board->cases[posToId(10, 5)], EAST);
        SET_WALL(board->cases[posToId(11, 5)], WEST);
        SET_WALL(board->cases[posToId(11, 5)], NORTH);
        SET_WALL(board->cases[posToId(15, 5)], NORTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(13, 6)], EAST);
        SET_WALL(board->cases[posToId(14, 6)], WEST);
        SET_WALL(board->cases[posToId(14, 6)], SOUTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);

        return;
    }

    if (pos == 2) {
        board->objectives[7] = posToId(1, 9);
        board->objectives[2] = posToId(4, 10);
        board->objectives[9] = posToId(6, 12);
        board->objectives[12] = posToId(2, 14);

        SET_WALL(board->cases[posToId(1, 8)], SOUTH);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(1, 9)], NORTH);
        SET_WALL(board->cases[posToId(1, 9)], EAST);
        SET_WALL(board->cases[posToId(2, 9)], WEST);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(0, 10)], SOUTH);
        SET_WALL(board->cases[posToId(4, 10)], SOUTH);
        SET_WALL(board->cases[posToId(4, 10)], EAST);
        SET_WALL(board->cases[posToId(5, 10)], WEST);
        SET_WALL(board->cases[posToId(0, 11)], NORTH);
        SET_WALL(board->cases[posToId(4, 11)], NORTH);
        SET_WALL(board->cases[posToId(6, 11)], SOUTH);
        SET_WALL(board->cases[posToId(5, 12)], EAST);
        SET_WALL(board->cases[posToId(6, 12)], WEST);
        SET_WALL(board->cases[posToId(6, 12)], NORTH);
        SET_WALL(board->cases[posToId(1, 14)], EAST);
        SET_WALL(board->cases[posToId(2, 14)], WEST);
        SET_WALL(board->cases[posToId(2, 14)], SOUTH);
        SET_WALL(board->cases[posToId(2, 15)], NORTH);
        SET_WALL(board->cases[posToId(4, 15)], EAST);
        SET_WALL(board->cases[posToId(5, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[9] = posToId(12, 9);
        board->objectives[2] = posToId(10, 11);
        board->objectives[12] = posToId(14, 13);
        board->objectives[7] = posToId(9, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(11, 9)], EAST);
        SET_WALL(board->cases[posToId(12, 9)], WEST);
        SET_WALL(board->cases[posToId(12, 9)], SOUTH);
        SET_WALL(board->cases[posToId(10, 10)], SOUTH);
        SET_WALL(board->cases[posToId(12, 10)], NORTH);
        SET_WALL(board->cases[posToId(15, 10)], SOUTH);
        SET_WALL(board->cases[posToId(10, 11)], NORTH);
        SET_WALL(board->cases[posToId(10, 11)], EAST);
        SET_WALL(board->cases[posToId(11, 11)], WEST);
        SET_WALL(board->cases[posToId(15, 11)], NORTH);
        SET_WALL(board->cases[posToId(9, 13)], SOUTH);
        SET_WALL(board->cases[posToId(14, 13)], SOUTH);
        SET_WALL(board->cases[posToId(14, 13)], EAST);
        SET_WALL(board->cases[posToId(15, 13)], WEST);
        SET_WALL(board->cases[posToId(8, 14)], EAST);
        SET_WALL(board->cases[posToId(9, 14)], WEST);
        SET_WALL(board->cases[posToId(9, 14)], NORTH);
        SET_WALL(board->cases[posToId(14, 14)], NORTH);
        SET_WALL(board->cases[posToId(10, 15)], EAST);
        SET_WALL(board->cases[posToId(11, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart7(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[6] = posToId(3, 1);
        board->objectives[3] = posToId(1, 2);
        board->objectives[16] = posToId(7, 3);
        board->objectives[8] = posToId(6, 5);
        board->objectives[13] = posToId(4, 6);

        SET_WALL(board->cases[posToId(3, 0)], SOUTH);
        SET_WALL(board->cases[posToId(4, 0)], EAST);
        SET_WALL(board->cases[posToId(5, 0)], WEST);
        SET_WALL(board->cases[posToId(3, 1)], NORTH);
        SET_WALL(board->cases[posToId(3, 1)], EAST);
        SET_WALL(board->cases[posToId(4, 1)], WEST);
        SET_WALL(board->cases[posToId(1, 2)], SOUTH);
        SET_WALL(board->cases[posToId(1, 2)], EAST);
        SET_WALL(board->cases[posToId(2, 2)], WEST);
        SET_WALL(board->cases[posToId(1, 3)], NORTH);
        SET_WALL(board->cases[posToId(7, 3)], SOUTH);
        SET_WALL(board->cases[posToId(7, 3)], EAST);
        SET_WALL(board->cases[posToId(0, 4)], SOUTH);
        SET_WALL(board->cases[posToId(7, 4)], NORTH);
        SET_WALL(board->cases[posToId(0, 5)], NORTH);
        SET_WALL(board->cases[posToId(4, 5)], SOUTH);
        SET_WALL(board->cases[posToId(5, 5)], EAST);
        SET_WALL(board->cases[posToId(6, 5)], WEST);
        SET_WALL(board->cases[posToId(6, 5)], SOUTH);
        SET_WALL(board->cases[posToId(3, 6)], EAST);
        SET_WALL(board->cases[posToId(4, 6)], WEST);
        SET_WALL(board->cases[posToId(4, 6)], NORTH);
        SET_WALL(board->cases[posToId(6, 6)], NORTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[3] = posToId(13, 1);
        board->objectives[6] = posToId(14, 3);
        board->objectives[13] = posToId(9, 4);
        board->objectives[8] = posToId(10, 6);
        board->objectives[16] = posToId(12, 7);

        SET_WALL(board->cases[posToId(10, 0)], EAST);
        SET_WALL(board->cases[posToId(11, 0)], WEST);
        SET_WALL(board->cases[posToId(11, 1)], EAST);
        SET_WALL(board->cases[posToId(12, 1)], WEST);
        SET_WALL(board->cases[posToId(12, 1)], SOUTH);
        SET_WALL(board->cases[posToId(13, 2)], NORTH);
        SET_WALL(board->cases[posToId(9, 3)], SOUTH);
        SET_WALL(board->cases[posToId(14, 3)], SOUTH);
        SET_WALL(board->cases[posToId(14, 3)], EAST);
        SET_WALL(board->cases[posToId(15, 3)], WEST);
        SET_WALL(board->cases[posToId(9, 4)], NORTH);
        SET_WALL(board->cases[posToId(9, 4)], EAST);
        SET_WALL(board->cases[posToId(10, 4)], WEST);
        SET_WALL(board->cases[posToId(14, 4)], NORTH);
        SET_WALL(board->cases[posToId(15, 4)], SOUTH);
        SET_WALL(board->cases[posToId(10, 5)], SOUTH);
        SET_WALL(board->cases[posToId(15, 5)], NORTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(9, 6)], EAST);
        SET_WALL(board->cases[posToId(10, 6)], WEST);
        SET_WALL(board->cases[posToId(10, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(11, 7)], EAST);
        SET_WALL(board->cases[posToId(12, 7)], WEST);
        SET_WALL(board->cases[posToId(12, 7)], SOUTH);

        return;
    }

    if (pos == 2) {
        board->objectives[16] = posToId(3, 8);
        board->objectives[8] = posToId(5, 9);
        board->objectives[13] = posToId(6, 11);
        board->objectives[6] = posToId(1, 12);
        board->objectives[3] = posToId(2, 14);

        SET_WALL(board->cases[posToId(3, 8)], NORTH);
        SET_WALL(board->cases[posToId(3, 8)], EAST);
        SET_WALL(board->cases[posToId(4, 8)], WEST);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(5, 9)], SOUTH);
        SET_WALL(board->cases[posToId(5, 9)], EAST);
        SET_WALL(board->cases[posToId(6, 9)], WEST);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(0, 10)], SOUTH);
        SET_WALL(board->cases[posToId(5, 10)], NORTH);
        SET_WALL(board->cases[posToId(0, 11)], NORTH);
        SET_WALL(board->cases[posToId(1, 11)], SOUTH);
        SET_WALL(board->cases[posToId(5, 11)], EAST);
        SET_WALL(board->cases[posToId(6, 11)], WEST);
        SET_WALL(board->cases[posToId(6, 11)], SOUTH);
        SET_WALL(board->cases[posToId(0, 12)], EAST);
        SET_WALL(board->cases[posToId(1, 12)], WEST);
        SET_WALL(board->cases[posToId(1, 12)], NORTH);
        SET_WALL(board->cases[posToId(6, 12)], NORTH);
        SET_WALL(board->cases[posToId(2, 13)], SOUTH);
        SET_WALL(board->cases[posToId(2, 14)], NORTH);
        SET_WALL(board->cases[posToId(2, 14)], EAST);
        SET_WALL(board->cases[posToId(3, 14)], WEST);
        SET_WALL(board->cases[posToId(4, 15)], EAST);
        SET_WALL(board->cases[posToId(5, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[13] = posToId(11, 9);
        board->objectives[8] = posToId(9, 10);
        board->objectives[16] = posToId(8, 12);
        board->objectives[3] = posToId(14, 13);
        board->objectives[6] = posToId(11, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(9, 9)], SOUTH);
        SET_WALL(board->cases[posToId(11, 9)], SOUTH);
        SET_WALL(board->cases[posToId(11, 9)], EAST);
        SET_WALL(board->cases[posToId(12, 9)], WEST);
        SET_WALL(board->cases[posToId(9, 10)], NORTH);
        SET_WALL(board->cases[posToId(9, 10)], EAST);
        SET_WALL(board->cases[posToId(10, 10)], WEST);
        SET_WALL(board->cases[posToId(11, 10)], NORTH);
        SET_WALL(board->cases[posToId(15, 10)], SOUTH);
        SET_WALL(board->cases[posToId(8, 11)], SOUTH);
        SET_WALL(board->cases[posToId(15, 11)], NORTH);
        SET_WALL(board->cases[posToId(8, 12)], WEST);
        SET_WALL(board->cases[posToId(8, 12)], NORTH);
        SET_WALL(board->cases[posToId(14, 12)], SOUTH);
        SET_WALL(board->cases[posToId(13, 13)], EAST);
        SET_WALL(board->cases[posToId(14, 13)], WEST);
        SET_WALL(board->cases[posToId(14, 13)], NORTH);
        SET_WALL(board->cases[posToId(11, 14)], EAST);
        SET_WALL(board->cases[posToId(12, 14)], WEST);
        SET_WALL(board->cases[posToId(12, 14)], SOUTH);
        SET_WALL(board->cases[posToId(10, 15)], EAST);
        SET_WALL(board->cases[posToId(11, 15)], WEST);
        SET_WALL(board->cases[posToId(12, 15)], NORTH);

        return;
    }
}

void ViewPlateauOfficiel::constructPart8(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[14] = posToId(6, 1);
        board->objectives[4] = posToId(4, 2);
        board->objectives[11] = posToId(2, 5);
        board->objectives[1] = posToId(5, 7);

        SET_WALL(board->cases[posToId(4, 0)], EAST);
        SET_WALL(board->cases[posToId(5, 0)], WEST);
        SET_WALL(board->cases[posToId(6, 0)], SOUTH);
        SET_WALL(board->cases[posToId(5, 1)], EAST);
        SET_WALL(board->cases[posToId(6, 1)], WEST);
        SET_WALL(board->cases[posToId(6, 1)], NORTH);
        SET_WALL(board->cases[posToId(3, 2)], EAST);
        SET_WALL(board->cases[posToId(4, 2)], WEST);
        SET_WALL(board->cases[posToId(4, 2)], SOUTH);
        SET_WALL(board->cases[posToId(0, 3)], SOUTH);
        SET_WALL(board->cases[posToId(4, 3)], NORTH);
        SET_WALL(board->cases[posToId(0, 4)], NORTH);
        SET_WALL(board->cases[posToId(2, 5)], SOUTH);
        SET_WALL(board->cases[posToId(2, 5)], EAST);
        SET_WALL(board->cases[posToId(3, 5)], WEST);
        SET_WALL(board->cases[posToId(2, 6)], NORTH);
        SET_WALL(board->cases[posToId(5, 6)], SOUTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(5, 7)], NORTH);
        SET_WALL(board->cases[posToId(5, 7)], EAST);
        SET_WALL(board->cases[posToId(6, 7)], WEST);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[11] = posToId(10, 2);
        board->objectives[4] = posToId(13, 4);
        board->objectives[1] = posToId(8, 5);
        board->objectives[14] = posToId(14, 6);

        SET_WALL(board->cases[posToId(11, 0)], EAST);
        SET_WALL(board->cases[posToId(12, 0)], WEST);
        SET_WALL(board->cases[posToId(9, 2)], EAST);
        SET_WALL(board->cases[posToId(10, 2)], WEST);
        SET_WALL(board->cases[posToId(10, 2)], SOUTH);
        SET_WALL(board->cases[posToId(10, 3)], NORTH);
        SET_WALL(board->cases[posToId(13, 3)], SOUTH);
        SET_WALL(board->cases[posToId(12, 4)], EAST);
        SET_WALL(board->cases[posToId(13, 4)], WEST);
        SET_WALL(board->cases[posToId(13, 4)], NORTH);
        SET_WALL(board->cases[posToId(15, 4)], SOUTH);
        SET_WALL(board->cases[posToId(8, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 5)], EAST);
        SET_WALL(board->cases[posToId(9, 5)], WEST);
        SET_WALL(board->cases[posToId(14, 5)], SOUTH);
        SET_WALL(board->cases[posToId(15, 5)], NORTH);
        SET_WALL(board->cases[posToId(8, 6)], NORTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(14, 6)], NORTH);
        SET_WALL(board->cases[posToId(14, 6)], EAST);
        SET_WALL(board->cases[posToId(15, 6)], WEST);
        SET_WALL(board->cases[posToId(9, 7)], WEST);

        return;
    }

    if (pos == 2) {
        board->objectives[14] = posToId(1, 9);
        board->objectives[1] = posToId(7, 10);
        board->objectives[4] = posToId(2, 11);
        board->objectives[11] = posToId(5, 13);

        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], EAST);
        SET_WALL(board->cases[posToId(1, 9)], WEST);
        SET_WALL(board->cases[posToId(1, 9)], SOUTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(7, 9)], SOUTH);
        SET_WALL(board->cases[posToId(0, 10)], SOUTH);
        SET_WALL(board->cases[posToId(1, 10)], NORTH);
        SET_WALL(board->cases[posToId(6, 10)], EAST);
        SET_WALL(board->cases[posToId(7, 10)], WEST);
        SET_WALL(board->cases[posToId(7, 10)], NORTH);
        SET_WALL(board->cases[posToId(0, 11)], NORTH);
        SET_WALL(board->cases[posToId(2, 11)], SOUTH);
        SET_WALL(board->cases[posToId(2, 11)], EAST);
        SET_WALL(board->cases[posToId(3, 11)], WEST);
        SET_WALL(board->cases[posToId(2, 12)], NORTH);
        SET_WALL(board->cases[posToId(5, 12)], SOUTH);
        SET_WALL(board->cases[posToId(5, 13)], NORTH);
        SET_WALL(board->cases[posToId(5, 13)], EAST);
        SET_WALL(board->cases[posToId(6, 13)], WEST);
        SET_WALL(board->cases[posToId(3, 15)], EAST);
        SET_WALL(board->cases[posToId(4, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[1] = posToId(10, 8);
        board->objectives[11] = posToId(13, 10);
        board->objectives[4] = posToId(11, 13);
        board->objectives[14] = posToId(9, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(9, 8)], EAST);
        SET_WALL(board->cases[posToId(10, 8)], WEST);
        SET_WALL(board->cases[posToId(10, 8)], SOUTH);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(10, 9)], NORTH);
        SET_WALL(board->cases[posToId(13, 9)], SOUTH);
        SET_WALL(board->cases[posToId(12, 10)], EAST);
        SET_WALL(board->cases[posToId(13, 10)], WEST);
        SET_WALL(board->cases[posToId(13, 10)], NORTH);
        SET_WALL(board->cases[posToId(15, 11)], SOUTH);
        SET_WALL(board->cases[posToId(11, 12)], SOUTH);
        SET_WALL(board->cases[posToId(15, 12)], NORTH);
        SET_WALL(board->cases[posToId(11, 13)], NORTH);
        SET_WALL(board->cases[posToId(11, 13)], EAST);
        SET_WALL(board->cases[posToId(12, 13)], WEST);
        SET_WALL(board->cases[posToId(9, 14)], SOUTH);
        SET_WALL(board->cases[posToId(9, 14)], EAST);
        SET_WALL(board->cases[posToId(10, 14)], WEST);
        SET_WALL(board->cases[posToId(9, 15)], NORTH);
        SET_WALL(board->cases[posToId(10, 15)], EAST);
        SET_WALL(board->cases[posToId(11, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart9(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[5] = posToId(2, 1);
        board->objectives[10] = posToId(6, 3);
        board->objectives[0] = posToId(1, 4);
        board->objectives[15] = posToId(3, 6);

        SET_WALL(board->cases[posToId(5, 0)], EAST);
        SET_WALL(board->cases[posToId(6, 0)], WEST);
        SET_WALL(board->cases[posToId(0, 1)], SOUTH);
        SET_WALL(board->cases[posToId(1, 1)], EAST);
        SET_WALL(board->cases[posToId(2, 1)], WEST);
        SET_WALL(board->cases[posToId(2, 1)], SOUTH);
        SET_WALL(board->cases[posToId(0, 2)], NORTH);
        SET_WALL(board->cases[posToId(2, 2)], NORTH);
        SET_WALL(board->cases[posToId(6, 2)], SOUTH);
        SET_WALL(board->cases[posToId(1, 3)], SOUTH);
        SET_WALL(board->cases[posToId(6, 3)], NORTH);
        SET_WALL(board->cases[posToId(6, 3)], EAST);
        SET_WALL(board->cases[posToId(7, 3)], WEST);
        SET_WALL(board->cases[posToId(0, 4)], EAST);
        SET_WALL(board->cases[posToId(1, 4)], WEST);
        SET_WALL(board->cases[posToId(1, 4)], NORTH);
        SET_WALL(board->cases[posToId(3, 6)], SOUTH);
        SET_WALL(board->cases[posToId(3, 6)], EAST);
        SET_WALL(board->cases[posToId(4, 6)], WEST);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(3, 7)], NORTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[0] = posToId(11, 1);
        board->objectives[5] = posToId(14, 2);
        board->objectives[15] = posToId(9, 3);
        board->objectives[10] = posToId(12, 6);

        SET_WALL(board->cases[posToId(11, 0)], SOUTH);
        SET_WALL(board->cases[posToId(13, 0)], EAST);
        SET_WALL(board->cases[posToId(14, 0)], WEST);
        SET_WALL(board->cases[posToId(11, 1)], NORTH);
        SET_WALL(board->cases[posToId(11, 1)], EAST);
        SET_WALL(board->cases[posToId(12, 1)], WEST);
        SET_WALL(board->cases[posToId(14, 1)], SOUTH);
        SET_WALL(board->cases[posToId(13, 2)], EAST);
        SET_WALL(board->cases[posToId(14, 2)], WEST);
        SET_WALL(board->cases[posToId(14, 2)], NORTH);
        SET_WALL(board->cases[posToId(8, 3)], EAST);
        SET_WALL(board->cases[posToId(9, 3)], WEST);
        SET_WALL(board->cases[posToId(9, 3)], SOUTH);
        SET_WALL(board->cases[posToId(9, 4)], NORTH);
        SET_WALL(board->cases[posToId(15, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(12, 6)], SOUTH);
        SET_WALL(board->cases[posToId(12, 6)], EAST);
        SET_WALL(board->cases[posToId(13, 6)], WEST);
        SET_WALL(board->cases[posToId(15, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(12, 7)], NORTH);

        return;
    }

    if (pos == 2) {
        board->objectives[10] = posToId(3, 9);
        board->objectives[15] = posToId(6, 12);
        board->objectives[5] = posToId(1, 13);
        board->objectives[0] = posToId(4, 14);

        SET_WALL(board->cases[posToId(3, 8)], SOUTH);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], SOUTH);
        SET_WALL(board->cases[posToId(2, 9)], EAST);
        SET_WALL(board->cases[posToId(3, 9)], WEST);
        SET_WALL(board->cases[posToId(3, 9)], NORTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(0, 10)], NORTH);
        SET_WALL(board->cases[posToId(6, 11)], SOUTH);
        SET_WALL(board->cases[posToId(6, 12)], NORTH);
        SET_WALL(board->cases[posToId(6, 12)], EAST);
        SET_WALL(board->cases[posToId(7, 12)], WEST);
        SET_WALL(board->cases[posToId(1, 13)], SOUTH);
        SET_WALL(board->cases[posToId(1, 13)], EAST);
        SET_WALL(board->cases[posToId(2, 13)], WEST);
        SET_WALL(board->cases[posToId(1, 14)], NORTH);
        SET_WALL(board->cases[posToId(3, 14)], EAST);
        SET_WALL(board->cases[posToId(4, 14)], WEST);
        SET_WALL(board->cases[posToId(4, 14)], SOUTH);
        SET_WALL(board->cases[posToId(1, 15)], EAST);
        SET_WALL(board->cases[posToId(2, 15)], WEST);
        SET_WALL(board->cases[posToId(4, 15)], NORTH);

        return;
    }

    if (pos == 3) {
        board->objectives[15] = posToId(12, 9);
        board->objectives[0] = posToId(14, 11);
        board->objectives[10] = posToId(9, 12);
        board->objectives[5] = posToId(13, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(12, 8)], SOUTH);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(11, 9)], EAST);
        SET_WALL(board->cases[posToId(12, 9)], WEST);
        SET_WALL(board->cases[posToId(12, 9)], NORTH);
        SET_WALL(board->cases[posToId(14, 11)], SOUTH);
        SET_WALL(board->cases[posToId(14, 11)], EAST);
        SET_WALL(board->cases[posToId(15, 11)], WEST);
        SET_WALL(board->cases[posToId(8, 12)], EAST);
        SET_WALL(board->cases[posToId(9, 12)], WEST);
        SET_WALL(board->cases[posToId(9, 12)], SOUTH);
        SET_WALL(board->cases[posToId(14, 12)], NORTH);
        SET_WALL(board->cases[posToId(9, 13)], NORTH);
        SET_WALL(board->cases[posToId(13, 13)], SOUTH);
        SET_WALL(board->cases[posToId(15, 13)], SOUTH);
        SET_WALL(board->cases[posToId(13, 14)], NORTH);
        SET_WALL(board->cases[posToId(13, 14)], EAST);
        SET_WALL(board->cases[posToId(14, 14)], WEST);
        SET_WALL(board->cases[posToId(15, 14)], NORTH);
        SET_WALL(board->cases[posToId(9, 15)], EAST);
        SET_WALL(board->cases[posToId(10, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart10(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[1] = posToId(3, 1);
        board->objectives[11] = posToId(6, 3);
        board->objectives[4] = posToId(1, 4);
        board->objectives[14] = posToId(5, 5);

        SET_WALL(board->cases[posToId(3, 0)], SOUTH);
        SET_WALL(board->cases[posToId(5, 0)], EAST);
        SET_WALL(board->cases[posToId(6, 0)], WEST);
        SET_WALL(board->cases[posToId(0, 1)], SOUTH);
        SET_WALL(board->cases[posToId(3, 1)], NORTH);
        SET_WALL(board->cases[posToId(3, 1)], EAST);
        SET_WALL(board->cases[posToId(4, 1)], WEST);
        SET_WALL(board->cases[posToId(0, 2)], NORTH);
        SET_WALL(board->cases[posToId(6, 3)], SOUTH);
        SET_WALL(board->cases[posToId(6, 3)], EAST);
        SET_WALL(board->cases[posToId(7, 3)], WEST);
        SET_WALL(board->cases[posToId(0, 4)], EAST);
        SET_WALL(board->cases[posToId(1, 4)], WEST);
        SET_WALL(board->cases[posToId(1, 4)], SOUTH);
        SET_WALL(board->cases[posToId(5, 4)], SOUTH);
        SET_WALL(board->cases[posToId(6, 4)], NORTH);
        SET_WALL(board->cases[posToId(1, 5)], NORTH);
        SET_WALL(board->cases[posToId(4, 5)], EAST);
        SET_WALL(board->cases[posToId(5, 5)], WEST);
        SET_WALL(board->cases[posToId(5, 5)], NORTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[4] = posToId(11, 1);
        board->objectives[1] = posToId(14, 3);
        board->objectives[14] = posToId(10, 5);
        board->objectives[11] = posToId(12, 6);

        SET_WALL(board->cases[posToId(11, 0)], SOUTH);
        SET_WALL(board->cases[posToId(13, 0)], EAST);
        SET_WALL(board->cases[posToId(14, 0)], WEST);
        SET_WALL(board->cases[posToId(10, 1)], EAST);
        SET_WALL(board->cases[posToId(11, 1)], WEST);
        SET_WALL(board->cases[posToId(11, 1)], NORTH);
        SET_WALL(board->cases[posToId(14, 3)], SOUTH);
        SET_WALL(board->cases[posToId(14, 3)], EAST);
        SET_WALL(board->cases[posToId(15, 3)], WEST);
        SET_WALL(board->cases[posToId(10, 4)], SOUTH);
        SET_WALL(board->cases[posToId(14, 4)], NORTH);
        SET_WALL(board->cases[posToId(10, 5)], NORTH);
        SET_WALL(board->cases[posToId(10, 5)], EAST);
        SET_WALL(board->cases[posToId(11, 5)], WEST);
        SET_WALL(board->cases[posToId(15, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(11, 6)], EAST);
        SET_WALL(board->cases[posToId(12, 6)], WEST);
        SET_WALL(board->cases[posToId(12, 6)], SOUTH);
        SET_WALL(board->cases[posToId(15, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(12, 7)], NORTH);

        return;
    }

    if (pos == 2) {
        board->objectives[11] = posToId(3, 9);
        board->objectives[14] = posToId(5, 10);
        board->objectives[1] = posToId(1, 12);
        board->objectives[4] = posToId(4, 14);

        SET_WALL(board->cases[posToId(3, 8)], SOUTH);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], SOUTH);
        SET_WALL(board->cases[posToId(3, 9)], NORTH);
        SET_WALL(board->cases[posToId(3, 9)], EAST);
        SET_WALL(board->cases[posToId(4, 9)], WEST);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(0, 10)], NORTH);
        SET_WALL(board->cases[posToId(4, 10)], EAST);
        SET_WALL(board->cases[posToId(5, 10)], WEST);
        SET_WALL(board->cases[posToId(5, 10)], SOUTH);
        SET_WALL(board->cases[posToId(1, 11)], SOUTH);
        SET_WALL(board->cases[posToId(5, 11)], NORTH);
        SET_WALL(board->cases[posToId(0, 12)], EAST);
        SET_WALL(board->cases[posToId(1, 12)], WEST);
        SET_WALL(board->cases[posToId(1, 12)], NORTH);
        SET_WALL(board->cases[posToId(4, 14)], SOUTH);
        SET_WALL(board->cases[posToId(4, 14)], EAST);
        SET_WALL(board->cases[posToId(5, 14)], WEST);
        SET_WALL(board->cases[posToId(1, 15)], EAST);
        SET_WALL(board->cases[posToId(2, 15)], WEST);
        SET_WALL(board->cases[posToId(4, 15)], NORTH);

        return;
    }

    if (pos == 3) {
        board->objectives[14] = posToId(10, 10);
        board->objectives[4] = posToId(14, 11);
        board->objectives[11] = posToId(9, 12);
        board->objectives[1] = posToId(12, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(10, 10)], SOUTH);
        SET_WALL(board->cases[posToId(10, 10)], EAST);
        SET_WALL(board->cases[posToId(11, 10)], WEST);
        SET_WALL(board->cases[posToId(14, 10)], SOUTH);
        SET_WALL(board->cases[posToId(9, 11)], SOUTH);
        SET_WALL(board->cases[posToId(10, 11)], NORTH);
        SET_WALL(board->cases[posToId(14, 11)], NORTH);
        SET_WALL(board->cases[posToId(14, 11)], EAST);
        SET_WALL(board->cases[posToId(15, 11)], WEST);
        SET_WALL(board->cases[posToId(8, 12)], EAST);
        SET_WALL(board->cases[posToId(9, 12)], WEST);
        SET_WALL(board->cases[posToId(9, 12)], NORTH);
        SET_WALL(board->cases[posToId(15, 13)], SOUTH);
        SET_WALL(board->cases[posToId(11, 14)], EAST);
        SET_WALL(board->cases[posToId(12, 14)], WEST);
        SET_WALL(board->cases[posToId(12, 14)], SOUTH);
        SET_WALL(board->cases[posToId(15, 14)], NORTH);
        SET_WALL(board->cases[posToId(9, 15)], EAST);
        SET_WALL(board->cases[posToId(10, 15)], WEST);
        SET_WALL(board->cases[posToId(12, 15)], NORTH);

        return;
    }
}

void ViewPlateauOfficiel::constructPart11(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[0] = posToId(4, 1);
        board->objectives[5] = posToId(1, 3);
        board->objectives[10] = posToId(6, 4);
        board->objectives[15] = posToId(3, 6);

        SET_WALL(board->cases[posToId(4, 0)], SOUTH);
        SET_WALL(board->cases[posToId(6, 0)], EAST);
        SET_WALL(board->cases[posToId(7, 0)], WEST);
        SET_WALL(board->cases[posToId(0, 1)], SOUTH);
        SET_WALL(board->cases[posToId(4, 1)], NORTH);
        SET_WALL(board->cases[posToId(4, 1)], EAST);
        SET_WALL(board->cases[posToId(5, 1)], WEST);
        SET_WALL(board->cases[posToId(0, 2)], NORTH);
        SET_WALL(board->cases[posToId(1, 2)], SOUTH);
        SET_WALL(board->cases[posToId(0, 3)], EAST);
        SET_WALL(board->cases[posToId(1, 3)], WEST);
        SET_WALL(board->cases[posToId(1, 3)], NORTH);
        SET_WALL(board->cases[posToId(5, 4)], EAST);
        SET_WALL(board->cases[posToId(6, 4)], WEST);
        SET_WALL(board->cases[posToId(6, 4)], SOUTH);
        SET_WALL(board->cases[posToId(3, 6)], SOUTH);
        SET_WALL(board->cases[posToId(3, 6)], EAST);
        SET_WALL(board->cases[posToId(4, 6)], WEST);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(3, 7)], NORTH);
        SET_WALL(board->cases[posToId(6, 7)], SOUTH);

        return;
    }

    if (pos == 1) {
        board->objectives[5] = posToId(12, 1);
        board->objectives[15] = posToId(9, 3);
        board->objectives[0] = posToId(14, 4);
        board->objectives[10] = posToId(11, 6);

        SET_WALL(board->cases[posToId(12, 0)], SOUTH);
        SET_WALL(board->cases[posToId(13, 0)], EAST);
        SET_WALL(board->cases[posToId(14, 0)], WEST);
        SET_WALL(board->cases[posToId(12, 1)], NORTH);
        SET_WALL(board->cases[posToId(12, 1)], EAST);
        SET_WALL(board->cases[posToId(13, 1)], WEST);
        SET_WALL(board->cases[posToId(8, 3)], EAST);
        SET_WALL(board->cases[posToId(9, 3)], WEST);
        SET_WALL(board->cases[posToId(9, 3)], SOUTH);
        SET_WALL(board->cases[posToId(9, 4)], NORTH);
        SET_WALL(board->cases[posToId(14, 4)], SOUTH);
        SET_WALL(board->cases[posToId(14, 4)], EAST);
        SET_WALL(board->cases[posToId(15, 4)], WEST);
        SET_WALL(board->cases[posToId(10, 5)], SOUTH);
        SET_WALL(board->cases[posToId(14, 5)], NORTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(10, 6)], EAST);
        SET_WALL(board->cases[posToId(11, 6)], WEST);
        SET_WALL(board->cases[posToId(11, 6)], NORTH);
        SET_WALL(board->cases[posToId(15, 6)], SOUTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(15, 7)], NORTH);

        return;
    }

    if (pos == 2) {
        board->objectives[10] = posToId(4, 9);
        board->objectives[0] = posToId(1, 11);
        board->objectives[15] = posToId(6, 12);
        board->objectives[5] = posToId(3, 14);

        SET_WALL(board->cases[posToId(0, 8)], SOUTH);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], NORTH);
        SET_WALL(board->cases[posToId(4, 9)], SOUTH);
        SET_WALL(board->cases[posToId(4, 9)], EAST);
        SET_WALL(board->cases[posToId(5, 9)], WEST);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(1, 10)], SOUTH);
        SET_WALL(board->cases[posToId(4, 10)], NORTH);
        SET_WALL(board->cases[posToId(0, 11)], EAST);
        SET_WALL(board->cases[posToId(1, 11)], WEST);
        SET_WALL(board->cases[posToId(1, 11)], NORTH);
        SET_WALL(board->cases[posToId(6, 11)], SOUTH);
        SET_WALL(board->cases[posToId(6, 12)], NORTH);
        SET_WALL(board->cases[posToId(6, 12)], EAST);
        SET_WALL(board->cases[posToId(7, 12)], WEST);
        SET_WALL(board->cases[posToId(2, 14)], EAST);
        SET_WALL(board->cases[posToId(3, 14)], WEST);
        SET_WALL(board->cases[posToId(3, 14)], SOUTH);
        SET_WALL(board->cases[posToId(1, 15)], EAST);
        SET_WALL(board->cases[posToId(2, 15)], WEST);
        SET_WALL(board->cases[posToId(3, 15)], NORTH);

        return;
    }

    if (pos == 3) {
        board->objectives[15] = posToId(12, 9);
        board->objectives[10] = posToId(9, 11);
        board->objectives[5] = posToId(14, 12);
        board->objectives[0] = posToId(11, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(12, 8)], SOUTH);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(11, 9)], EAST);
        SET_WALL(board->cases[posToId(12, 9)], WEST);
        SET_WALL(board->cases[posToId(12, 9)], NORTH);
        SET_WALL(board->cases[posToId(9, 10)], SOUTH);
        SET_WALL(board->cases[posToId(9, 11)], NORTH);
        SET_WALL(board->cases[posToId(9, 11)], EAST);
        SET_WALL(board->cases[posToId(10, 11)], WEST);
        SET_WALL(board->cases[posToId(14, 12)], SOUTH);
        SET_WALL(board->cases[posToId(14, 12)], EAST);
        SET_WALL(board->cases[posToId(15, 12)], WEST);
        SET_WALL(board->cases[posToId(14, 13)], NORTH);
        SET_WALL(board->cases[posToId(15, 13)], SOUTH);
        SET_WALL(board->cases[posToId(10, 14)], EAST);
        SET_WALL(board->cases[posToId(11, 14)], WEST);
        SET_WALL(board->cases[posToId(11, 14)], SOUTH);
        SET_WALL(board->cases[posToId(15, 14)], NORTH);
        SET_WALL(board->cases[posToId(8, 15)], EAST);
        SET_WALL(board->cases[posToId(9, 15)], WEST);
        SET_WALL(board->cases[posToId(11, 15)], NORTH);

        return;
    }
}

void ViewPlateauOfficiel::constructPart12(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[2] = posToId(4, 2);
        board->objectives[12] = posToId(2, 3);
        board->objectives[7] = posToId(5, 4);
        board->objectives[9] = posToId(3, 5);

        SET_WALL(board->cases[posToId(3, 0)], EAST);
        SET_WALL(board->cases[posToId(4, 0)], WEST);
        SET_WALL(board->cases[posToId(2, 2)], SOUTH);
        SET_WALL(board->cases[posToId(3, 2)], EAST);
        SET_WALL(board->cases[posToId(4, 2)], WEST);
        SET_WALL(board->cases[posToId(4, 2)], SOUTH);
        SET_WALL(board->cases[posToId(1, 3)], EAST);
        SET_WALL(board->cases[posToId(2, 3)], WEST);
        SET_WALL(board->cases[posToId(2, 3)], NORTH);
        SET_WALL(board->cases[posToId(4, 3)], NORTH);
        SET_WALL(board->cases[posToId(3, 4)], SOUTH);
        SET_WALL(board->cases[posToId(5, 4)], SOUTH);
        SET_WALL(board->cases[posToId(5, 4)], EAST);
        SET_WALL(board->cases[posToId(6, 4)], WEST);
        SET_WALL(board->cases[posToId(0, 5)], SOUTH);
        SET_WALL(board->cases[posToId(3, 5)], NORTH);
        SET_WALL(board->cases[posToId(3, 5)], EAST);
        SET_WALL(board->cases[posToId(4, 5)], WEST);
        SET_WALL(board->cases[posToId(5, 5)], NORTH);
        SET_WALL(board->cases[posToId(0, 6)], NORTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[12] = posToId(12, 10);
        board->objectives[9] = posToId(10, 11);
        board->objectives[2] = posToId(12, 12);
        board->objectives[7] = posToId(11, 13);

        SET_WALL(board->cases[posToId(9, 0)], EAST);
        SET_WALL(board->cases[posToId(10, 0)], WEST);
        SET_WALL(board->cases[posToId(12, 1)], SOUTH);
        SET_WALL(board->cases[posToId(12, 2)], NORTH);
        SET_WALL(board->cases[posToId(12, 2)], EAST);
        SET_WALL(board->cases[posToId(13, 2)], WEST);
        SET_WALL(board->cases[posToId(10, 3)], SOUTH);
        SET_WALL(board->cases[posToId(10, 3)], EAST);
        SET_WALL(board->cases[posToId(11, 3)], WEST);
        SET_WALL(board->cases[posToId(13, 3)], SOUTH);
        SET_WALL(board->cases[posToId(15, 3)], SOUTH);
        SET_WALL(board->cases[posToId(10, 4)], NORTH);
        SET_WALL(board->cases[posToId(12, 4)], EAST);
        SET_WALL(board->cases[posToId(13, 4)], WEST);
        SET_WALL(board->cases[posToId(13, 4)], NORTH);
        SET_WALL(board->cases[posToId(15, 4)], NORTH);
        SET_WALL(board->cases[posToId(10, 5)], WEST);
        SET_WALL(board->cases[posToId(11, 5)], EAST);
        SET_WALL(board->cases[posToId(11, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(11, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);

        return;
    }

    if (pos == 2) {
        board->objectives[7] = posToId(4, 10);
        board->objectives[2] = posToId(2, 11);
        board->objectives[9] = posToId(5, 12);
        board->objectives[12] = posToId(3, 13);

        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(4, 9)], SOUTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(4, 10)], NORTH);
        SET_WALL(board->cases[posToId(4, 10)], EAST);
        SET_WALL(board->cases[posToId(5, 10)], WEST);
        SET_WALL(board->cases[posToId(0, 11)], SOUTH);
        SET_WALL(board->cases[posToId(2, 11)], SOUTH);
        SET_WALL(board->cases[posToId(2, 11)], EAST);
        SET_WALL(board->cases[posToId(5, 11)], WEST);
        SET_WALL(board->cases[posToId(5, 11)], SOUTH);
        SET_WALL(board->cases[posToId(0, 12)], NORTH);
        SET_WALL(board->cases[posToId(2, 12)], NORTH);
        SET_WALL(board->cases[posToId(4, 12)], EAST);
        SET_WALL(board->cases[posToId(5, 12)], WEST);
        SET_WALL(board->cases[posToId(5, 12)], NORTH);
        SET_WALL(board->cases[posToId(2, 13)], EAST);
        SET_WALL(board->cases[posToId(3, 13)], WEST);
        SET_WALL(board->cases[posToId(3, 13)], SOUTH);
        SET_WALL(board->cases[posToId(3, 14)], NORTH);
        SET_WALL(board->cases[posToId(5, 15)], EAST);
        SET_WALL(board->cases[posToId(6, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[9] = posToId(12, 10);
        board->objectives[7] = posToId(10, 11);
        board->objectives[12] = posToId(13, 12);
        board->objectives[2] = posToId(11, 13);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(15, 9)], SOUTH);
        SET_WALL(board->cases[posToId(10, 10)], SOUTH);
        SET_WALL(board->cases[posToId(11, 10)], EAST);
        SET_WALL(board->cases[posToId(12, 10)], WEST);
        SET_WALL(board->cases[posToId(12, 10)], SOUTH);
        SET_WALL(board->cases[posToId(15, 10)], NORTH);
        SET_WALL(board->cases[posToId(9, 11)], WEST);
        SET_WALL(board->cases[posToId(10, 11)], EAST);
        SET_WALL(board->cases[posToId(10, 11)], NORTH);
        SET_WALL(board->cases[posToId(12, 11)], NORTH);
        SET_WALL(board->cases[posToId(11, 12)], SOUTH);
        SET_WALL(board->cases[posToId(13, 12)], SOUTH);
        SET_WALL(board->cases[posToId(13, 12)], EAST);
        SET_WALL(board->cases[posToId(14, 12)], WEST);
        SET_WALL(board->cases[posToId(11, 13)], NORTH);
        SET_WALL(board->cases[posToId(11, 13)], EAST);
        SET_WALL(board->cases[posToId(12, 13)], WEST);
        SET_WALL(board->cases[posToId(13, 13)], NORTH);
        SET_WALL(board->cases[posToId(11, 15)], EAST);
        SET_WALL(board->cases[posToId(12, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart13(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[4] = posToId(4, 2);
        board->objectives[1] = posToId(4, 3);
        board->objectives[14] = posToId(6, 5);
        board->objectives[11] = posToId(2, 6);

        SET_WALL(board->cases[posToId(1, 0)], EAST);
        SET_WALL(board->cases[posToId(2, 0)], WEST);
        SET_WALL(board->cases[posToId(3, 2)], EAST);
        SET_WALL(board->cases[posToId(4, 2)], WEST);
        SET_WALL(board->cases[posToId(4, 2)], SOUTH);
        SET_WALL(board->cases[posToId(4, 3)], NORTH);
        SET_WALL(board->cases[posToId(4, 3)], EAST);
        SET_WALL(board->cases[posToId(5, 3)], WEST);
        SET_WALL(board->cases[posToId(0, 4)], SOUTH);
        SET_WALL(board->cases[posToId(6, 4)], SOUTH);
        SET_WALL(board->cases[posToId(0, 5)], NORTH);
        SET_WALL(board->cases[posToId(5, 5)], EAST);
        SET_WALL(board->cases[posToId(6, 5)], WEST);
        SET_WALL(board->cases[posToId(6, 5)], NORTH);
        SET_WALL(board->cases[posToId(2, 6)], SOUTH);
        SET_WALL(board->cases[posToId(2, 6)], EAST);
        SET_WALL(board->cases[posToId(3, 6)], WEST);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(2, 7)], NORTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[11] = posToId(9, 2);
        board->objectives[1] = posToId(12, 12);
        board->objectives[4] = posToId(13, 12);
        board->objectives[14] = posToId(10, 14);

        SET_WALL(board->cases[posToId(10, 0)], EAST);
        SET_WALL(board->cases[posToId(11, 0)], WEST);
        SET_WALL(board->cases[posToId(8, 2)], EAST);
        SET_WALL(board->cases[posToId(9, 2)], WEST);
        SET_WALL(board->cases[posToId(9, 2)], SOUTH);
        SET_WALL(board->cases[posToId(15, 2)], SOUTH);
        SET_WALL(board->cases[posToId(9, 3)], NORTH);
        SET_WALL(board->cases[posToId(13, 3)], SOUTH);
        SET_WALL(board->cases[posToId(15, 3)], NORTH);
        SET_WALL(board->cases[posToId(12, 4)], SOUTH);
        SET_WALL(board->cases[posToId(12, 4)], EAST);
        SET_WALL(board->cases[posToId(13, 4)], WEST);
        SET_WALL(board->cases[posToId(13, 4)], NORTH);
        SET_WALL(board->cases[posToId(10, 5)], SOUTH);
        SET_WALL(board->cases[posToId(12, 5)], NORTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(10, 6)], NORTH);
        SET_WALL(board->cases[posToId(10, 6)], EAST);
        SET_WALL(board->cases[posToId(11, 6)], WEST);
        SET_WALL(board->cases[posToId(9, 7)], WEST);

        return;
    }

    if (pos == 2) {
        board->objectives[14] = posToId(5, 9);
        board->objectives[4] = posToId(2, 11);
        board->objectives[1] = posToId(3, 11);
        board->objectives[11] = posToId(6, 13);

        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(4, 9)], EAST);
        SET_WALL(board->cases[posToId(5, 9)], WEST);
        SET_WALL(board->cases[posToId(5, 9)], SOUTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(3, 10)], SOUTH);
        SET_WALL(board->cases[posToId(5, 10)], NORTH);
        SET_WALL(board->cases[posToId(2, 11)], SOUTH);
        SET_WALL(board->cases[posToId(2, 11)], EAST);
        SET_WALL(board->cases[posToId(3, 11)], WEST);
        SET_WALL(board->cases[posToId(3, 11)], NORTH);
        SET_WALL(board->cases[posToId(0, 12)], SOUTH);
        SET_WALL(board->cases[posToId(2, 12)], NORTH);
        SET_WALL(board->cases[posToId(6, 12)], SOUTH);
        SET_WALL(board->cases[posToId(0, 13)], NORTH);
        SET_WALL(board->cases[posToId(6, 13)], NORTH);
        SET_WALL(board->cases[posToId(6, 13)], EAST);
        SET_WALL(board->cases[posToId(7, 13)], WEST);
        SET_WALL(board->cases[posToId(4, 15)], EAST);
        SET_WALL(board->cases[posToId(5, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[11] = posToId(13, 9);
        board->objectives[14] = posToId(9, 10);
        board->objectives[1] = posToId(11, 12);
        board->objectives[4] = posToId(11, 13);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(13, 8)], SOUTH);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(12, 9)], EAST);
        SET_WALL(board->cases[posToId(13, 9)], WEST);
        SET_WALL(board->cases[posToId(13, 9)], NORTH);
        SET_WALL(board->cases[posToId(9, 10)], SOUTH);
        SET_WALL(board->cases[posToId(9, 10)], EAST);
        SET_WALL(board->cases[posToId(10, 10)], WEST);
        SET_WALL(board->cases[posToId(15, 10)], SOUTH);
        SET_WALL(board->cases[posToId(9, 11)], NORTH);
        SET_WALL(board->cases[posToId(15, 11)], NORTH);
        SET_WALL(board->cases[posToId(10, 12)], EAST);
        SET_WALL(board->cases[posToId(11, 12)], WEST);
        SET_WALL(board->cases[posToId(11, 12)], SOUTH);
        SET_WALL(board->cases[posToId(11, 13)], NORTH);
        SET_WALL(board->cases[posToId(11, 13)], EAST);
        SET_WALL(board->cases[posToId(12, 13)], WEST);
        SET_WALL(board->cases[posToId(12, 15)], EAST);
        SET_WALL(board->cases[posToId(13, 15)], WEST);

        return;
    }
}

void ViewPlateauOfficiel::constructPart14(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[2] = posToId(5, 1);
        board->objectives[9] = posToId(7, 4);
        board->objectives[7] = posToId(2, 5);
        board->objectives[12] = posToId(2, 6);

        SET_WALL(board->cases[posToId(5, 0)], SOUTH);
        SET_WALL(board->cases[posToId(6, 0)], EAST);
        SET_WALL(board->cases[posToId(7, 0)], WEST);
        SET_WALL(board->cases[posToId(5, 1)], NORTH);
        SET_WALL(board->cases[posToId(5, 1)], EAST);
        SET_WALL(board->cases[posToId(6, 1)], WEST);
        SET_WALL(board->cases[posToId(0, 2)], SOUTH);
        SET_WALL(board->cases[posToId(0, 3)], NORTH);
        SET_WALL(board->cases[posToId(6, 4)], EAST);
        SET_WALL(board->cases[posToId(7, 4)], WEST);
        SET_WALL(board->cases[posToId(7, 4)], SOUTH);
        SET_WALL(board->cases[posToId(2, 5)], SOUTH);
        SET_WALL(board->cases[posToId(3, 5)], EAST);
        SET_WALL(board->cases[posToId(3, 5)], WEST);
        SET_WALL(board->cases[posToId(7, 5)], NORTH);
        SET_WALL(board->cases[posToId(1, 6)], EAST);
        SET_WALL(board->cases[posToId(2, 6)], WEST);
        SET_WALL(board->cases[posToId(2, 6)], NORTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[12] = posToId(9, 2);
        board->objectives[7] = posToId(10, 2);
        board->objectives[2] = posToId(14, 5);
        board->objectives[9] = posToId(11, 7);

        SET_WALL(board->cases[posToId(12, 0)], EAST);
        SET_WALL(board->cases[posToId(13, 0)], WEST);
        SET_WALL(board->cases[posToId(9, 1)], SOUTH);
        SET_WALL(board->cases[posToId(9, 2)], NORTH);
        SET_WALL(board->cases[posToId(9, 2)], EAST);
        SET_WALL(board->cases[posToId(10, 2)], WEST);
        SET_WALL(board->cases[posToId(10, 2)], SOUTH);
        SET_WALL(board->cases[posToId(10, 3)], NORTH);
        SET_WALL(board->cases[posToId(14, 5)], SOUTH);
        SET_WALL(board->cases[posToId(14, 5)], EAST);
        SET_WALL(board->cases[posToId(15, 5)], WEST);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(11, 6)], SOUTH);
        SET_WALL(board->cases[posToId(14, 6)], NORTH);
        SET_WALL(board->cases[posToId(15, 6)], SOUTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(10, 7)], EAST);
        SET_WALL(board->cases[posToId(11, 7)], WEST);
        SET_WALL(board->cases[posToId(11, 7)], NORTH);
        SET_WALL(board->cases[posToId(15, 7)], NORTH);

        return;
    }

    if (pos == 2) {
        board->objectives[9] = posToId(4, 8);
        board->objectives[2] = posToId(1, 10);
        board->objectives[7] = posToId(5, 13);
        board->objectives[12] = posToId(6, 13);

        SET_WALL(board->cases[posToId(0, 8)], SOUTH);
        SET_WALL(board->cases[posToId(4, 8)], SOUTH);
        SET_WALL(board->cases[posToId(4, 8)], EAST);
        SET_WALL(board->cases[posToId(5, 8)], WEST);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], NORTH);
        SET_WALL(board->cases[posToId(1, 9)], SOUTH);
        SET_WALL(board->cases[posToId(4, 9)], NORTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(0, 10)], EAST);
        SET_WALL(board->cases[posToId(1, 10)], WEST);
        SET_WALL(board->cases[posToId(1, 10)], NORTH);
        SET_WALL(board->cases[posToId(5, 13)], NORTH);
        SET_WALL(board->cases[posToId(5, 13)], EAST);
        SET_WALL(board->cases[posToId(6, 13)], WEST);
        SET_WALL(board->cases[posToId(6, 13)], SOUTH);
        SET_WALL(board->cases[posToId(6, 14)], NORTH);
        SET_WALL(board->cases[posToId(2, 15)], EAST);
        SET_WALL(board->cases[posToId(3, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[12] = posToId(13, 9);
        board->objectives[7] = posToId(13, 10);
        board->objectives[9] = posToId(8, 11);
        board->objectives[2] = posToId(10, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(13, 9)], SOUTH);
        SET_WALL(board->cases[posToId(13, 9)], EAST);
        SET_WALL(board->cases[posToId(14, 9)], WEST);
        SET_WALL(board->cases[posToId(8, 10)], SOUTH);
        SET_WALL(board->cases[posToId(12, 10)], EAST);
        SET_WALL(board->cases[posToId(13, 10)], WEST);
        SET_WALL(board->cases[posToId(13, 10)], NORTH);
        SET_WALL(board->cases[posToId(8, 11)], NORTH);
        SET_WALL(board->cases[posToId(8, 11)], EAST);
        SET_WALL(board->cases[posToId(9, 11)], WEST);
        SET_WALL(board->cases[posToId(15, 12)], SOUTH);
        SET_WALL(board->cases[posToId(15, 12)], NORTH);
        SET_WALL(board->cases[posToId(9, 13)], EAST);
        SET_WALL(board->cases[posToId(10, 13)], WEST);
        SET_WALL(board->cases[posToId(10, 13)], SOUTH);
        SET_WALL(board->cases[posToId(8, 14)], EAST);
        SET_WALL(board->cases[posToId(9, 14)], WEST);
        SET_WALL(board->cases[posToId(10, 14)], NORTH);

        return;
    }
}

void ViewPlateauOfficiel::constructPart15(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[5] = posToId(2, 1);
        board->objectives[0] = posToId(6, 3);
        board->objectives[15] = posToId(1, 6);
        board->objectives[10] = posToId(5, 6);

        SET_WALL(board->cases[posToId(2, 0)], SOUTH);
        SET_WALL(board->cases[posToId(5, 0)], EAST);
        SET_WALL(board->cases[posToId(6, 0)], WEST);
        SET_WALL(board->cases[posToId(1, 1)], EAST);
        SET_WALL(board->cases[posToId(2, 1)], WEST);
        SET_WALL(board->cases[posToId(2, 1)], NORTH);
        SET_WALL(board->cases[posToId(6, 2)], SOUTH);
        SET_WALL(board->cases[posToId(6, 3)], NORTH);
        SET_WALL(board->cases[posToId(6, 3)], EAST);
        SET_WALL(board->cases[posToId(7, 3)], WEST);
        SET_WALL(board->cases[posToId(0, 4)], SOUTH);
        SET_WALL(board->cases[posToId(0, 5)], NORTH);
        SET_WALL(board->cases[posToId(1, 6)], SOUTH);
        SET_WALL(board->cases[posToId(1, 6)], EAST);
        SET_WALL(board->cases[posToId(2, 6)], WEST);
        SET_WALL(board->cases[posToId(4, 6)], EAST);
        SET_WALL(board->cases[posToId(5, 6)], WEST);
        SET_WALL(board->cases[posToId(5, 6)], SOUTH);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(1, 7)], NORTH);
        SET_WALL(board->cases[posToId(5, 7)], NORTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[15] = posToId(9, 1);
        board->objectives[5] = posToId(14, 2);
        board->objectives[10] = posToId(9, 5);
        board->objectives[0] = posToId(12, 6);

        SET_WALL(board->cases[posToId(10, 0)], EAST);
        SET_WALL(board->cases[posToId(11, 0)], WEST);
        SET_WALL(board->cases[posToId(8, 1)], EAST);
        SET_WALL(board->cases[posToId(9, 1)], WEST);
        SET_WALL(board->cases[posToId(9, 1)], SOUTH);
        SET_WALL(board->cases[posToId(14, 1)], SOUTH);
        SET_WALL(board->cases[posToId(9, 2)], NORTH);
        SET_WALL(board->cases[posToId(14, 2)], NORTH);
        SET_WALL(board->cases[posToId(14, 2)], EAST);
        SET_WALL(board->cases[posToId(15, 2)], WEST);
        SET_WALL(board->cases[posToId(9, 4)], SOUTH);
        SET_WALL(board->cases[posToId(8, 5)], EAST);
        SET_WALL(board->cases[posToId(9, 5)], WEST);
        SET_WALL(board->cases[posToId(9, 5)], NORTH);
        SET_WALL(board->cases[posToId(15, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(12, 6)], SOUTH);
        SET_WALL(board->cases[posToId(12, 6)], EAST);
        SET_WALL(board->cases[posToId(13, 6)], WEST);
        SET_WALL(board->cases[posToId(15, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(12, 7)], NORTH);

        return;
    }

    if (pos == 2) {
        board->objectives[0] = posToId(3, 9);
        board->objectives[10] = posToId(6, 10);
        board->objectives[5] = posToId(1, 13);
        board->objectives[15] = posToId(6, 14);

        SET_WALL(board->cases[posToId(3, 8)], SOUTH);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], SOUTH);
        SET_WALL(board->cases[posToId(2, 9)], EAST);
        SET_WALL(board->cases[posToId(3, 9)], WEST);
        SET_WALL(board->cases[posToId(3, 9)], NORTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(0, 10)], NORTH);
        SET_WALL(board->cases[posToId(6, 10)], SOUTH);
        SET_WALL(board->cases[posToId(6, 10)], EAST);
        SET_WALL(board->cases[posToId(7, 10)], WEST);
        SET_WALL(board->cases[posToId(6, 11)], NORTH);
        SET_WALL(board->cases[posToId(1, 13)], EAST);
        SET_WALL(board->cases[posToId(2, 13)], WEST);
        SET_WALL(board->cases[posToId(2, 13)], SOUTH);
        SET_WALL(board->cases[posToId(6, 13)], SOUTH);
        SET_WALL(board->cases[posToId(1, 14)], NORTH);
        SET_WALL(board->cases[posToId(6, 14)], NORTH);
        SET_WALL(board->cases[posToId(6, 14)], EAST);
        SET_WALL(board->cases[posToId(7, 14)], WEST);
        SET_WALL(board->cases[posToId(4, 15)], EAST);
        SET_WALL(board->cases[posToId(5, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[10] = posToId(10, 9);
        board->objectives[15] = posToId(14, 9);
        board->objectives[0] = posToId(9, 12);
        board->objectives[5] = posToId(13, 14);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(10, 8)], SOUTH);
        SET_WALL(board->cases[posToId(14, 8)], SOUTH);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(10, 9)], NORTH);
        SET_WALL(board->cases[posToId(10, 9)], EAST);
        SET_WALL(board->cases[posToId(11, 9)], WEST);
        SET_WALL(board->cases[posToId(13, 9)], EAST);
        SET_WALL(board->cases[posToId(14, 9)], WEST);
        SET_WALL(board->cases[posToId(14, 9)], NORTH);
        SET_WALL(board->cases[posToId(15, 10)], SOUTH);
        SET_WALL(board->cases[posToId(15, 11)], NORTH);
        SET_WALL(board->cases[posToId(8, 12)], EAST);
        SET_WALL(board->cases[posToId(9, 12)], WEST);
        SET_WALL(board->cases[posToId(9, 12)], SOUTH);
        SET_WALL(board->cases[posToId(9, 13)], NORTH);
        SET_WALL(board->cases[posToId(13, 14)], SOUTH);
        SET_WALL(board->cases[posToId(13, 14)], EAST);
        SET_WALL(board->cases[posToId(14, 14)], WEST);
        SET_WALL(board->cases[posToId(9, 15)], EAST);
        SET_WALL(board->cases[posToId(10, 15)], WEST);
        SET_WALL(board->cases[posToId(13, 15)], NORTH);

        return;
    }
}

void ViewPlateauOfficiel::constructPart16(Board* board, int pos) {
    if (pos == 0) {
        board->objectives[0] = posToId(3, 1);
        board->objectives[5] = posToId(6, 2);
        board->objectives[10] = posToId(6, 3);
        board->objectives[15] = posToId(4, 6);

        SET_WALL(board->cases[posToId(3, 0)], SOUTH);
        SET_WALL(board->cases[posToId(5, 0)], EAST);
        SET_WALL(board->cases[posToId(6, 0)], WEST);
        SET_WALL(board->cases[posToId(2, 1)], EAST);
        SET_WALL(board->cases[posToId(3, 1)], WEST);
        SET_WALL(board->cases[posToId(3, 1)], NORTH);
        SET_WALL(board->cases[posToId(5, 2)], EAST);
        SET_WALL(board->cases[posToId(6, 2)], WEST);
        SET_WALL(board->cases[posToId(6, 2)], SOUTH);
        SET_WALL(board->cases[posToId(6, 3)], NORTH);
        SET_WALL(board->cases[posToId(6, 3)], EAST);
        SET_WALL(board->cases[posToId(7, 3)], WEST);
        SET_WALL(board->cases[posToId(0, 5)], SOUTH);
        SET_WALL(board->cases[posToId(0, 6)], NORTH);
        SET_WALL(board->cases[posToId(4, 6)], SOUTH);
        SET_WALL(board->cases[posToId(4, 6)], EAST);
        SET_WALL(board->cases[posToId(5, 6)], WEST);
        SET_WALL(board->cases[posToId(7, 6)], SOUTH);
        SET_WALL(board->cases[posToId(4, 7)], NORTH);
        SET_WALL(board->cases[posToId(6, 7)], EAST);

        return;
    }

    if (pos == 1) {
        board->objectives[0] = posToId(14, 3);
        board->objectives[5] = posToId(13, 14);
        board->objectives[10] = posToId(12, 14);
        board->objectives[15] = posToId(9, 4);

        SET_WALL(board->cases[posToId(9, 0)], EAST);
        SET_WALL(board->cases[posToId(10, 0)], WEST);
        SET_WALL(board->cases[posToId(14, 2)], SOUTH);
        SET_WALL(board->cases[posToId(14, 3)], NORTH);
        SET_WALL(board->cases[posToId(14, 3)], EAST);
        SET_WALL(board->cases[posToId(15, 3)], WEST);
        SET_WALL(board->cases[posToId(8, 4)], EAST);
        SET_WALL(board->cases[posToId(9, 4)], WEST);
        SET_WALL(board->cases[posToId(9, 4)], SOUTH);
        SET_WALL(board->cases[posToId(9, 5)], NORTH);
        SET_WALL(board->cases[posToId(13, 5)], SOUTH);
        SET_WALL(board->cases[posToId(15, 5)], SOUTH);
        SET_WALL(board->cases[posToId(8, 6)], SOUTH);
        SET_WALL(board->cases[posToId(12, 6)], SOUTH);
        SET_WALL(board->cases[posToId(12, 6)], EAST);
        SET_WALL(board->cases[posToId(13, 6)], WEST);
        SET_WALL(board->cases[posToId(13, 6)], NORTH);
        SET_WALL(board->cases[posToId(15, 6)], NORTH);
        SET_WALL(board->cases[posToId(9, 7)], WEST);
        SET_WALL(board->cases[posToId(12, 7)], NORTH);

        return;
    }

    if (pos == 2) {
        board->objectives[0] = posToId(1, 12);
        board->objectives[5] = posToId(2, 9);
        board->objectives[10] = posToId(3, 9);
        board->objectives[15] = posToId(6, 11);

        SET_WALL(board->cases[posToId(3, 8)], SOUTH);
        SET_WALL(board->cases[posToId(6, 8)], EAST);
        SET_WALL(board->cases[posToId(0, 9)], SOUTH);
        SET_WALL(board->cases[posToId(2, 9)], SOUTH);
        SET_WALL(board->cases[posToId(2, 9)], EAST);
        SET_WALL(board->cases[posToId(3, 9)], WEST);
        SET_WALL(board->cases[posToId(3, 9)], NORTH);
        SET_WALL(board->cases[posToId(7, 9)], NORTH);
        SET_WALL(board->cases[posToId(0, 10)], NORTH);
        SET_WALL(board->cases[posToId(2, 10)], NORTH);
        SET_WALL(board->cases[posToId(6, 10)], SOUTH);
        SET_WALL(board->cases[posToId(6, 11)], NORTH);
        SET_WALL(board->cases[posToId(6, 11)], EAST);
        SET_WALL(board->cases[posToId(7, 11)], WEST);
        SET_WALL(board->cases[posToId(0, 12)], EAST);
        SET_WALL(board->cases[posToId(1, 12)], WEST);
        SET_WALL(board->cases[posToId(1, 12)], SOUTH);
        SET_WALL(board->cases[posToId(1, 13)], NORTH);
        SET_WALL(board->cases[posToId(5, 15)], EAST);
        SET_WALL(board->cases[posToId(6, 15)], WEST);

        return;
    }

    if (pos == 3) {
        board->objectives[0] = posToId(12, 14);
        board->objectives[5] = posToId(9, 13);
        board->objectives[10] = posToId(9, 12);
        board->objectives[15] = posToId(11, 9);

        SET_WALL(board->cases[posToId(9, 8)], WEST);
        SET_WALL(board->cases[posToId(11, 8)], SOUTH);
        SET_WALL(board->cases[posToId(8, 9)], NORTH);
        SET_WALL(board->cases[posToId(10, 9)], EAST);
        SET_WALL(board->cases[posToId(11, 9)], WEST);
        SET_WALL(board->cases[posToId(11, 9)], NORTH);
        SET_WALL(board->cases[posToId(15, 9)], SOUTH);
        SET_WALL(board->cases[posToId(15, 10)], NORTH);
        SET_WALL(board->cases[posToId(8, 12)], EAST);
        SET_WALL(board->cases[posToId(9, 12)], WEST);
        SET_WALL(board->cases[posToId(9, 12)], SOUTH);
        SET_WALL(board->cases[posToId(9, 13)], NORTH);
        SET_WALL(board->cases[posToId(9, 13)], EAST);
        SET_WALL(board->cases[posToId(10, 13)], WEST);
        SET_WALL(board->cases[posToId(12, 14)], SOUTH);
        SET_WALL(board->cases[posToId(12, 14)], EAST);
        SET_WALL(board->cases[posToId(13, 14)], WEST);
        SET_WALL(board->cases[posToId(9, 14)], EAST);
        SET_WALL(board->cases[posToId(10, 14)], WEST);
        SET_WALL(board->cases[posToId(13, 14)], NORTH);

        return;
    }
}
