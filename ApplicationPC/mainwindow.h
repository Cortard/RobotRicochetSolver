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
    void on_Histoire1_clicked();

    void handleMovement();

    void on_resetPlateau_clicked();
    void on_Sauvegarder_clicked();
    void on_Home_clicked();
    void on_ModeOfficiel_clicked();
    void on_ModeLibre_clicked();
    void on_ModeCharger_clicked();
    void on_ModeCreer_clicked();
    void on_ModeJouer_clicked();
    void on_ModeEdition_clicked();
    void on_BtnCharger_clicked();
    void on_JouerOfficiel_clicked();
    void on_Solution_clicked();
    void on_Rejouer_clicked();
    void on_ModeHistoire_clicked();
    void on_ModeEntrainement_clicked();
    void on_GenererAleatoire_clicked();
    void on_AddObj_clicked();
    void on_AddRbt_clicked();
    void on_Jouer_clicked();

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
