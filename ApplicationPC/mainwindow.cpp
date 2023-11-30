#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <iostream>

MainWindow::MainWindow(QWidget *parent, Board* bd)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    viewBoard(nullptr),
    board(bd)
{
    ui->setupUi(this);

    viewMenu = new viewMainMenu(ui->stackedWidget->widget(1)->findChild<QWidget*>("mainmenuwindow"));
    viewPlato = new viewPlateau(ui->stackedWidget->widget(2)->findChild<QWidget*>("pageplateau"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonJouer_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagejouer);

    if (!viewBoard) {
        viewBoard = new ViewBoard(board);
        ui->stackedWidget->widget(1)->findChild<QGraphicsView*>()->setScene(viewBoard);
        viewBoard->setParent(ui->stackedWidget->widget(1)->findChild<QGraphicsView*>());
    }
    ui->stackedWidget->setCurrentIndex(1);
}

//void MainWindow::on_pushButton_6_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
//}
//void MainWindow::on_pushHistoire_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->pagehistoire);
//}
//void MainWindow::on_Retour_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->pagejouer);
//}
//void MainWindow::on_Home_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
//}
//void MainWindow::on_Retour_3_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->pagejouer);
//}
//void MainWindow::on_Home_2_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
//}
//void MainWindow::on_Retour_5_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->pagejouer);
//}
//void MainWindow::on_pushTrain_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->pagetrain);
//}
//void MainWindow::on_Home_3_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
//}
//void MainWindow::on_Retour_4_clicked()
//{
//    ui->stackedWidget->setCurrentWidget(ui->pagetrain);
//}

void MainWindow::on_pushObjective_clicked()
{
//    for(int i=0;i<16;i++){
//        if(board->objectives.at(i)!=-1){
//            ControllerAddObj(board).control(i,135);
//        }
//    }

    ControllerAddObj(board).control();
}

void MainWindow::on_pushWall_clicked()
{

}

void MainWindow::on_pushButton_21_clicked()
{

}

