#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "viewboard.h"
#include "viewmainmenu.h"
#include "viewplateau.h"
#include "viewplateauofficiel.h"
#include "QGridLayout"
#include <QLabel>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Board* = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonJouer_clicked();
    void on_pushHistoire_clicked();
    void on_Retour_clicked();
    void on_Retour_3_clicked();
    void on_Home_2_clicked();
    void on_Retour_5_clicked();
    void on_pushTrain_clicked();
    void on_Home_3_clicked();
    void on_Retour_4_clicked();
    void on_pushObjective_clicked();
    void on_pushButton_21_clicked();
    void on_pushRobot_clicked();
    void on_pushTrain_2_clicked();
    void on_pushPlateau_clicked();
    void on_Home_5_clicked();
    void handleMovement();
    void on_pushTrain_3_clicked();
    void on_pushHistoire_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_buttonhistoire1_clicked();
    void on_Home_4_clicked();
    void on_Retour_15_clicked();
    void on_Retour_17_clicked();
    void on_resetPlateau_clicked();
    void on_pushObjective_3_clicked();
    void on_pushButton_12_clicked();

    void on_pushSave_clicked();

private:
    Ui::MainWindow *ui;
    Board* board;
    ViewBoard *viewBoard;
    viewMainMenu *viewMenu;
    viewPlateau *viewPlato;
    ViewPlateauOfficiel *viewPlateauOfficiel;

    QLabel *selectedLabel;

    int solutionid=0;
    QString direction;
    int rbt;

};
#endif // MAINWINDOW_H
