#include "board.h"
#include <iostream>

Board::Board() {
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i) {
        cases[i] = 0;
    }
}

int Board::getIndex(int x, int y) const {
    return x + y * BOARD_SIZE;
}

void Board::addWall(int x, int y, char dir) {
    if (dir == 'N') {
        y += 1;
    }

    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        int index = getIndex(x, y);
        cases[index] = 1;
    } else {
        std::cerr << "Erreur : Coordonnées hors limites.\n";
    }
}

void Board::addObjective(int x, int y, int id) {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        int index = getIndex(x, y);
        objectives[id] = index;
    } else {
        std::cerr << "Erreur : Coordonnées hors limites.\n";
    }
}

int Board::getBoardSize() {
    return BOARD_SIZE;
}

void ShapeManager::moveShape(QPointF pos)
{
    if (selected == nullptr) return;

    selected->pos = pos;
}
