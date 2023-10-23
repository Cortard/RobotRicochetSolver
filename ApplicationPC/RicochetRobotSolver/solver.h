#ifndef SOLVER_H
#define SOLVER_H

#include <QVector>

#include "settings.h"
#include "board.h"

class Solver {
private:
    QVector<unsigned int> solution;

public:
    Solver();

    bool const connect();
    QVector<unsigned int> const getSolution();
    void calcSolution(Board *board);
};

#endif // SOLVER_H
