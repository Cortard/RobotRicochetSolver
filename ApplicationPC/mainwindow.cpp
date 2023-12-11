#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <iostream>

MainWindow::MainWindow(QWidget *parent, Board* bd)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    viewBoard(nullptr),
    viewPlato(nullptr),
    board(bd)
{
    ui->setupUi(this);

    viewMenu = new viewMainMenu(ui->stackedWidget->widget(1)->findChild<QWidget*>("mainmenuwindow"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonJouer_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagejouer);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}
void MainWindow::on_pushHistoire_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagehistoire);
}
void MainWindow::on_Retour_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}
void MainWindow::on_Home_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}
void MainWindow::on_Retour_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagejouer);
}
void MainWindow::on_Home_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}
void MainWindow::on_Retour_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagejouer);
}
void MainWindow::on_pushTrain_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagetrain);
}
void MainWindow::on_Home_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}
void MainWindow::on_Retour_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagetrain);
}

void MainWindow::on_pushObjective_clicked()
{
    bool found = false;
    for (const auto& pair : board->objectives) {
        if (pair.second == 135) {
            found = true;
            break;
        }
    }
    if (!found) {
        ControllerAddObj(board).control();
    }

}

void MainWindow::on_pushWall_clicked()
{

}

void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->edition);
}

void MainWindow::on_pushRobot_clicked()
{
    bool found = false;
    for (const auto& pair : board->robots) {
        if (pair.second == 136) {
            found = true;
            break;
        }
    }
    if (!found) {
        ControllerAddRobot(board).control();
    }
}


void MainWindow::on_Retour_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}


void MainWindow::on_pushTrain_2_clicked()
{
    if (!viewBoard) {
        viewBoard = new ViewBoard(board);
        ui->stackedWidget->widget(1)->findChild<QGraphicsView*>()->setScene(viewBoard);
        viewBoard->setParent(ui->stackedWidget->widget(1)->findChild<QGraphicsView*>());
    }
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushPlateau_clicked()
{
    if (!viewPlato) {
        viewPlato = new viewPlateau(board);
        ui->stackedWidget->widget(1)->findChild<QGraphicsView*>()->setScene(viewPlato);
        viewPlato->setParent(ui->stackedWidget->widget(1)->findChild<QGraphicsView*>());
    }
    ui->stackedWidget->setCurrentWidget(ui->plateau);
}

