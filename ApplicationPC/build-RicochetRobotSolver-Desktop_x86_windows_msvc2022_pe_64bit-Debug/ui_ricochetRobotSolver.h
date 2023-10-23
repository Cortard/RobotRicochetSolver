/********************************************************************************
** Form generated from reading UI file 'ricochetRobotSolver.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RICOCHETROBOTSOLVER_H
#define UI_RICOCHETROBOTSOLVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RicochetRobotSolver
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *RicochetRobotSolver)
    {
        if (RicochetRobotSolver->objectName().isEmpty())
            RicochetRobotSolver->setObjectName("RicochetRobotSolver");
        RicochetRobotSolver->resize(1280, 720);
        centralwidget = new QWidget(RicochetRobotSolver);
        centralwidget->setObjectName("centralwidget");
        RicochetRobotSolver->setCentralWidget(centralwidget);

        retranslateUi(RicochetRobotSolver);

        QMetaObject::connectSlotsByName(RicochetRobotSolver);
    } // setupUi

    void retranslateUi(QMainWindow *RicochetRobotSolver)
    {
        RicochetRobotSolver->setWindowTitle(QCoreApplication::translate("RicochetRobotSolver", "RicochetRobotSolver", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RicochetRobotSolver: public Ui_RicochetRobotSolver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RICOCHETROBOTSOLVER_H
