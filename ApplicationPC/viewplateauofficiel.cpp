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
                        item->setPos(530,10);
                    }else if(col==2){
                        item->setRotation(90);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,10);
                    }else if(col==3){
                        item->setRotation(270);
                        item->setTransformOriginPoint(origin);
                        item->setPos(530,210);
                    }else if(col==4){
                        item->setRotation(180);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,210);
                    }
                    addItem(item);
                }else if(secondClickPos.x()<930 && secondClickPos.y()<210 && secondClickPos.y()>10 && secondClickPos.x()>730){
                    item->setScale(0.65);
                    QPointF origin = item->transformOriginPoint();
                    item->setTransformOriginPoint(item->boundingRect().center());

                    if(col==1){
                        item->setRotation(90);
                        item->setTransformOriginPoint(origin);
                        item->setPos(930,10);
                    }else if(col==2){
                        item->setRotation(180);
                        item->setTransformOriginPoint(origin);
                        item->setPos(930,210);
                    }else if(col==3){
                        item->setRotation(0);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,10);
                    }else if(col==4){
                        item->setRotation(270);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,210);
                    }
                    addItem(item);
                }else if(secondClickPos.x()<730 && secondClickPos.y()<410 && secondClickPos.y()>210 && secondClickPos.x()>530){
                    item->setScale(0.65);
                    QPointF origin = item->transformOriginPoint();
                    item->setTransformOriginPoint(item->boundingRect().center());

                    if(col==1){
                        item->setRotation(270);
                        item->setTransformOriginPoint(origin);
                        item->setPos(530,410);
                    }else if(col==2){
                        item->setRotation(0);
                        item->setTransformOriginPoint(origin);
                        item->setPos(530,210);
                    }else if(col==3){
                        item->setRotation(180);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,410);
                    }else if(col==4){
                        item->setRotation(90);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,210);
                    }
                    addItem(item);
                }else if(secondClickPos.x()<930 && secondClickPos.y()<410 && secondClickPos.y()>210 && secondClickPos.x()>730){
                    item->setScale(0.65);
                    QPointF origin = item->transformOriginPoint();
                    item->setTransformOriginPoint(item->boundingRect().center());

                    if(col==1){
                        item->setRotation(180);
                        item->setTransformOriginPoint(origin);
                        item->setPos(930,410);
                    }else if(col==2){
                        item->setRotation(270);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,410);
                    }else if(col==3){
                        item->setRotation(90);
                        item->setTransformOriginPoint(origin);
                        item->setPos(930,210);
                    }else if(col==4){
                        item->setRotation(0);
                        item->setTransformOriginPoint(origin);
                        item->setPos(730,210);
                    }
                    addItem(item);
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
