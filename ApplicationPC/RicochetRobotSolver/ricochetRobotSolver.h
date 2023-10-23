#ifndef RICOCHETROBOTSOLVER_H
#define RICOCHETROBOTSOLVER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class RicochetRobotSolver; }
QT_END_NAMESPACE

class RicochetRobotSolver : public QMainWindow {
    Q_OBJECT

private:
    Ui::RicochetRobotSolver *ui;

public:
    RicochetRobotSolver(QWidget *parent = nullptr);
    ~RicochetRobotSolver();
};

#endif // RICOCHETROBOTSOLVER_H
