#include "ricochetRobotSolver.h"
#include "ui_ricochetRobotSolver.h"

RicochetRobotSolver::RicochetRobotSolver(QWidget *parent) : QMainWindow(parent), ui(new Ui::RicochetRobotSolver) {
    ui->setupUi(this);
}

RicochetRobotSolver::~RicochetRobotSolver() {
    delete ui;
}

