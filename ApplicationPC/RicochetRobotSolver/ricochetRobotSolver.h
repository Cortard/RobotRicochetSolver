#ifndef RICOCHETROBOTSOLVER_H
#define RICOCHETROBOTSOLVER_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class RicochetRobotSolver; }
QT_END_NAMESPACE

class RicochetRobotSolver : public QMainWindow {
    Q_OBJECT

private:
    Ui::RicochetRobotSolver *ui;
    QWidget* currentPage;

public:
    RicochetRobotSolver(QWidget *parent = nullptr);

    void setCurrentPage(QWidget* newPage);

    ~RicochetRobotSolver();
};

#endif // RICOCHETROBOTSOLVER_H
