#include "viewboard.h".h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

ViewBoard::ViewBoard() : QGraphicsScene()
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


            lines.push_back(topLine);
            lines.push_back(leftLine);
            lines.push_back(bottomLine);
            lines.push_back(rightLine);
        }
    }

    update();
}


void ViewBoard::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        // Récupérer la position de la souris dans la scène
        QPointF mousePos = mouseEvent->scenePos();

        // Définir une tolérance pour déterminer si la souris est assez proche de la ligne
        const qreal tolerance = 10.0;

        // Parcourir les lignes pour détecter celle qui a été cliquée
        for (QGraphicsLineItem* line : lines) {
            QLineF lineGeometry = line->line();
            if (QLineF(mousePos, lineGeometry.center()).length() < tolerance) {
                // La souris est assez proche de cette ligne, ajustez l'épaisseur

                QPen pen = line->pen();
                if(pen.width()!=3){
                    pen.setWidth(3); // Ajustez l'épaisseur selon vos besoins
                }else{
                    pen.setWidth(1);
                }
                line->setPen(pen);
                break;  // Quittez la boucle après avoir ajusté une seule ligne
            }
        }
    }

    // Appeler la mise à jour de la scène
    update();
}



