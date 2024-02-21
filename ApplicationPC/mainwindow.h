#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "viewboard.h"
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
    void onAddObjectivesButtonClick();
    void onAddRobotButtonClick();
    void onLoadButtonClick();
    void onLoadModeButtonClick();
    void onCreateModeButtonClick();
    void onEditModeButtonClick();
    void onTrainModeButtonClick();
    void onHistoryModeButtonClick();
    void onPlayModeButtonClick();
    void onPlayButtonClick();
    void onPlayOfficialButtonClick();
    void onOfficialModeButtonClick();
    void onFreeModeButtonClick();
    void onSettingsModeButtonClick();
    void onGenerateButtonClick();
    void onHomeButtonClick();
    void onPlayAgainButtonClick();
    void onSaveButtonClick();
    void onResetButtonClick();
    void onSolveButtonClick();
    void onHistory1ButtonClick();

    void handleMovement();

private:
    Ui::MainWindow *ui;
    Board* board;
    ViewBoard *viewBoard;
    viewPlateau *viewPlato;
    ViewPlateauOfficiel *viewPlateauOfficiel;

    QLabel *selectedLabel;

    int solutionid=0;
    QString direction;
    int rbt;
    int fichier=0;
    bool pass = true;
    int wall=0;

};
#endif // MAINWINDOW_H
