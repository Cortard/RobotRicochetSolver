#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <iostream>

#include <QGuiApplication>
#include <QScreen>
#include <QtGlobal>
#include <QTime>
#include "socketconnection.h"
#include <QThread>
#include <QFile>

MainWindow::MainWindow(QWidget *parent, Board* bd)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      board(bd)
{
    ui->setupUi(this);

    ui->radioButton->setChecked(true);

    viewBoard = nullptr;
    viewPlato = nullptr;
    viewPlateauOfficiel = nullptr;

    viewMenu = new viewMainMenu(ui->stackedWidget->widget(1)->findChild<QWidget*>("mainmenuwindow"));

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    move((screenGeometry.width() - width()) / 2, (screenGeometry.height() - height()) / 2);

    //connect(ui->graphicsView_5, SIGNAL(clicked(const QPointF&)), this, SLOT(onGraphicsViewClicked(const QPointF&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleMovement() {
    board->mouvement++;
    ui->label->setText(QString::number(board->mouvement));
}

void MainWindow::on_pushButtonJouer_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagejouer);
}
void MainWindow::on_pushHistoire_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagehistoire);
}
void MainWindow::on_Retour_clicked()
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

void MainWindow::on_pushTrain_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->choixplateau);
}


void MainWindow::on_pushPlateau_clicked()
{
    if (viewPlato == nullptr) {
        viewPlato = new viewPlateau(board);
        ui->stackedWidget->widget(6)->findChild<QGraphicsView*>()->setScene(viewPlato);
        viewPlato->setParent(ui->stackedWidget->widget(6)->findChild<QGraphicsView*>());
        connect(viewPlato, &viewPlateau::movementOccurred, this, &MainWindow::handleMovement);
    }
    //SocketConnection::getSolution(board);
    board->robots2=board->robots;
    ui->stackedWidget->setCurrentWidget(ui->plateau);
}


void MainWindow::on_Home_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}


void MainWindow::on_pushTrain_3_clicked()
{
    if (viewBoard == nullptr) {
        viewBoard = new ViewBoard(board);
        ui->stackedWidget->widget(1)->findChild<QGraphicsView*>()->setScene(viewBoard);
        viewBoard->setParent(ui->stackedWidget->widget(1)->findChild<QGraphicsView*>());
    }
    ui->stackedWidget->setCurrentWidget(ui->pageplateau);
}


void MainWindow::on_pushHistoire_3_clicked()
{
    if (viewPlateauOfficiel == nullptr) {
        viewPlateauOfficiel = new ViewPlateauOfficiel(board);
        ui->stackedWidget->widget(8)->findChild<QGraphicsView*>()->setScene(viewPlateauOfficiel);
        viewPlateauOfficiel->setParent(ui->stackedWidget->widget(8)->findChild<QGraphicsView*>());
    }
    ui->stackedWidget->setCurrentWidget(ui->plateauofficiel);
}


void MainWindow::on_pushButton_clicked()
{
    if (viewBoard == nullptr) {
        viewBoard = new ViewBoard(board);
        ui->stackedWidget->widget(1)->findChild<QGraphicsView*>()->setScene(viewBoard);
        viewBoard->setParent(ui->stackedWidget->widget(1)->findChild<QGraphicsView*>());
    }
    ui->stackedWidget->setCurrentWidget(ui->pageplateau);
}


void MainWindow::on_pushButton_5_clicked()
{
    if(ui->radioButton->isChecked()){

        int rand1 = rand() % 16;
        srand(QTime::currentTime().msec()+rand1);
        int rand2 = rand() % 16;
        srand(QTime::currentTime().msec()+rand2);
        int rand3 = rand() % 16;
        srand(QTime::currentTime().msec()+rand3);
        int rand4 = rand() % 16;
        srand(QTime::currentTime().msec()+rand4);

        switch (rand1) {
        case 0:
            viewPlateauOfficiel->constructPart1(this->board, 0);
            break;
        case 1:
            viewPlateauOfficiel->constructPart5(this->board, 0);
            break;
        case 2:
            viewPlateauOfficiel->constructPart9(this->board, 0);
            break;
        case 3:
            viewPlateauOfficiel->constructPart13(this->board, 0);
            break;
        case 4:
            viewPlateauOfficiel->constructPart2(this->board, 0);
            break;
        case 5:
            viewPlateauOfficiel->constructPart6(this->board, 0);
            break;
        case 6:
            viewPlateauOfficiel->constructPart10(this->board, 0);
            break;
        case 7:
            viewPlateauOfficiel->constructPart14(this->board, 0);
            break;
        case 8:
            viewPlateauOfficiel->constructPart3(this->board, 0);
            break;
        case 9:
            viewPlateauOfficiel->constructPart7(this->board, 0);
            break;
        case 10:
            viewPlateauOfficiel->constructPart11(this->board, 0);
            break;
        case 11:
            viewPlateauOfficiel->constructPart15(this->board, 0);
            break;
        case 12:
            viewPlateauOfficiel->constructPart4(this->board, 0);
            break;
        case 13:
            viewPlateauOfficiel->constructPart8(this->board, 0);
            break;
        case 14:
            viewPlateauOfficiel->constructPart12(this->board, 0);
            break;
        case 15:
            viewPlateauOfficiel->constructPart16(this->board, 0);
            break;
        }

        switch (rand2) {
        case 0:
            viewPlateauOfficiel->constructPart1(this->board, 1);
            break;
        case 1:
            viewPlateauOfficiel->constructPart5(this->board, 1);
            break;
        case 2:
            viewPlateauOfficiel->constructPart9(this->board, 1);
            break;
        case 3:
            viewPlateauOfficiel->constructPart13(this->board, 1);
            break;
        case 4:
            viewPlateauOfficiel->constructPart2(this->board, 1);
            break;
        case 5:
            viewPlateauOfficiel->constructPart6(this->board, 1);
            break;
        case 6:
            viewPlateauOfficiel->constructPart10(this->board, 1);
            break;
        case 7:
            viewPlateauOfficiel->constructPart14(this->board, 1);
            break;
        case 8:
            viewPlateauOfficiel->constructPart3(this->board, 1);
            break;
        case 9:
            viewPlateauOfficiel->constructPart7(this->board, 1);
            break;
        case 10:
            viewPlateauOfficiel->constructPart11(this->board, 1);
            break;
        case 11:
            viewPlateauOfficiel->constructPart15(this->board, 1);
            break;
        case 12:
            viewPlateauOfficiel->constructPart4(this->board, 1);
            break;
        case 13:
            viewPlateauOfficiel->constructPart8(this->board, 1);
            break;
        case 14:
            viewPlateauOfficiel->constructPart12(this->board, 1);
            break;
        case 15:
            viewPlateauOfficiel->constructPart16(this->board, 1);
            break;
        }

        switch (rand3) {
        case 0:
            viewPlateauOfficiel->constructPart1(this->board, 2);
            break;
        case 1:
            viewPlateauOfficiel->constructPart5(this->board, 2);
            break;
        case 2:
            viewPlateauOfficiel->constructPart9(this->board, 2);
            break;
        case 3:
            viewPlateauOfficiel->constructPart13(this->board, 2);
            break;
        case 4:
            viewPlateauOfficiel->constructPart2(this->board, 2);
            break;
        case 5:
            viewPlateauOfficiel->constructPart6(this->board, 2);
            break;
        case 6:
            viewPlateauOfficiel->constructPart10(this->board, 2);
            break;
        case 7:
            viewPlateauOfficiel->constructPart14(this->board, 2);
            break;
        case 8:
            viewPlateauOfficiel->constructPart3(this->board, 2);
            break;
        case 9:
            viewPlateauOfficiel->constructPart7(this->board, 2);
            break;
        case 10:
            viewPlateauOfficiel->constructPart11(this->board, 2);
            break;
        case 11:
            viewPlateauOfficiel->constructPart15(this->board, 2);
            break;
        case 12:
            viewPlateauOfficiel->constructPart4(this->board, 2);
            break;
        case 13:
            viewPlateauOfficiel->constructPart8(this->board, 2);
            break;
        case 14:
            viewPlateauOfficiel->constructPart12(this->board, 2);
            break;
        case 15:
            viewPlateauOfficiel->constructPart16(this->board, 2);
            break;
        }

        switch (rand4) {
        case 0:
            viewPlateauOfficiel->constructPart1(this->board, 3);
            break;
        case 1:
            viewPlateauOfficiel->constructPart5(this->board, 3);
            break;
        case 2:
            viewPlateauOfficiel->constructPart9(this->board, 3);
            break;
        case 3:
            viewPlateauOfficiel->constructPart13(this->board, 3);
            break;
        case 4:
            viewPlateauOfficiel->constructPart2(this->board, 3);
            break;
        case 5:
            viewPlateauOfficiel->constructPart6(this->board, 3);
            break;
        case 6:
            viewPlateauOfficiel->constructPart10(this->board, 3);
            break;
        case 7:
            viewPlateauOfficiel->constructPart14(this->board, 3);
            break;
        case 8:
            viewPlateauOfficiel->constructPart3(this->board, 3);
            break;
        case 9:
            viewPlateauOfficiel->constructPart7(this->board, 3);
            break;
        case 10:
            viewPlateauOfficiel->constructPart11(this->board, 3);
            break;
        case 11:
            viewPlateauOfficiel->constructPart15(this->board, 3);
            break;
        case 12:
            viewPlateauOfficiel->constructPart4(this->board, 3);
            break;
        case 13:
            viewPlateauOfficiel->constructPart8(this->board, 3);
            break;
        case 14:
            viewPlateauOfficiel->constructPart12(this->board, 3);
            break;
        case 15:
            viewPlateauOfficiel->constructPart16(this->board, 3);
            break;
        }

        if (viewPlato == nullptr) {
            viewPlato = new viewPlateau(board);
            ui->stackedWidget->widget(6)->findChild<QGraphicsView*>()->setScene(viewPlato);
            viewPlato->setParent(ui->stackedWidget->widget(6)->findChild<QGraphicsView*>());
            connect(viewPlato, &viewPlateau::movementOccurred, this, &MainWindow::handleMovement);
        }
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}


void MainWindow::on_buttonhistoire1_clicked()
{
    this->board->reset();
    viewPlateauOfficiel->constructPart13(this->board, 0);
    viewPlateauOfficiel->constructPart15(this->board, 1);
    viewPlateauOfficiel->constructPart2(this->board, 2);
    viewPlateauOfficiel->constructPart3(this->board, 3);
    this->board->addRobot(0,2);
    this->board->addRobot(1,250);
    this->board->addRobot(2,55);
    this->board->addRobot(3,86);
    this->board->objJeu=0;

    //SocketConnection::getSolution(board);
    this->board->robots2=this->board->robots;

    if (viewPlato == nullptr) {
        viewPlato = new viewPlateau(board);
        ui->stackedWidget->widget(6)->findChild<QGraphicsView*>()->setScene(viewPlato);
        viewPlato->setParent(ui->stackedWidget->widget(6)->findChild<QGraphicsView*>());
        connect(viewPlato, &viewPlateau::movementOccurred, this, &MainWindow::handleMovement);
    }
    ui->stackedWidget->setCurrentWidget(ui->plateau);
}


void MainWindow::on_Home_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}

void MainWindow::on_Retour_15_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}


void MainWindow::on_Retour_17_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}


void MainWindow::on_resetPlateau_clicked()
{
    this->board->reset();
}


void MainWindow::on_pushObjective_3_clicked()
{
    board->robots=board->robots2;
    solutionid=0;
    board->notifyObserver();
    if (viewBoard == nullptr) {
        viewBoard = new ViewBoard(board);
        ui->stackedWidget->widget(1)->findChild<QGraphicsView*>()->setScene(viewBoard);
        viewBoard->setParent(ui->stackedWidget->widget(1)->findChild<QGraphicsView*>());
    }
    ui->stackedWidget->setCurrentWidget(ui->pageplateau);
}

void MainWindow::on_pushButton_12_clicked()
{
    if(solutionid==0){
        board->robots=board->robots2;
        board->notifyObserver();
    }

    if(GET_DIRECTION(board->path[solutionid])==1){
        direction="NORTH";
    }else if(GET_DIRECTION(board->path[solutionid])==2){
        direction="EAST";
    }else if(GET_DIRECTION(board->path[solutionid])==4){
        direction="SOUTH";
    }else if(GET_DIRECTION(board->path[solutionid])==8){
        direction="WEST";
    }

    if(GET_ROBOT(board->path[solutionid])==0){
        rbt=0;
    }else if(GET_ROBOT(board->path[solutionid])==1){
        rbt=1;
    }else if(GET_ROBOT(board->path[solutionid])==2){
        rbt=2;
    }else if(GET_ROBOT(board->path[solutionid])==3){
        rbt=3;
    }

    int col = board->robots.at(rbt) % 16;
    int row = board->robots.at(rbt) / 16;

    int compPos=-1;


    if(direction=="NORTH"){
        for(int i=row;i>=0;i--){
            if (HAS_WALL(board->cases[col + i * 16], NORTH) == 1){
                compPos = (col + i * 16);
                break;
            }
        }

        int targetRow = -1;
        int targetCol = col;

        for (int i = 0; i < row ; i++){
            int pos = col + i * 16;
            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });
            if (it != board->robots.end()){
                targetRow = i;
            }
        }
        int targetPos = targetCol + targetRow * 16;
        if(compPos <= targetPos+16){
            board->moveRobot(rbt,targetPos+16);
        }else{
            board->moveRobot(rbt,compPos);
        }
    }
    if(direction=="EAST"){
        for(int i=col;i<16;i++){
            if (HAS_WALL(board->cases[i + row * 16], EAST) == 2){
                compPos = (i + row * 16);
                break;
            }
        }

        int targetRow = row;
        int targetCol = -1;

        for (int i = col+1 ; i <= 16 ; i++){
            int pos = i + row * 16;

            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });
            if (it != board->robots.end()){
                targetCol = i;
                break;
            }
        }

        int targetPos = targetCol + targetRow * 16;

        if(targetPos <= compPos && targetCol!=-1 ){
            board->moveRobot(rbt,targetPos-1);
        }else{
            board->moveRobot(rbt,compPos);
        }
    }
    if(direction=="SOUTH"){
        for(int i=row;i<=16;i++){
            if (HAS_WALL(board->cases[col + i * 16], SOUTH) == 4){
                compPos = (col + i * 16);
                break;
            }
        }

        int targetRow = -1;
        int targetCol = col;

        for (int i = row+1 ; i <= 16 ; i++){
            int pos = col + i * 16;
            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });
            if (it != board->robots.end()){
                targetRow = i;
                break;
            }
        }

        int targetPos = targetCol + targetRow * 16;

        if(targetPos <= compPos && targetRow!=-1 ){
            board->moveRobot(rbt,targetPos-16);
        }else{
            board->moveRobot(rbt,compPos);
        }
    }
    if(direction=="WEST"){
        for(int i=col;i>=0;i--){
            if (HAS_WALL(board->cases[i + row * 16], WEST) == 8){
                compPos = (i + row * 16);
                break;
            }
        }

        int targetRow = row;
        int targetCol = -1;

        for (int i = col-1 ; i >= 0 ; i--){
            int pos = i + row * 16;
            auto it = std::find_if(board->robots.begin(), board->robots.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });
            if (it != board->robots.end()){
                targetCol = i;
                break;
            }
        }

        int targetPos = targetCol + targetRow * 16;

        if(targetPos >= compPos && targetCol!=-1 ){
            board->moveRobot(rbt,targetPos+1);
        }else{
            board->moveRobot(rbt,compPos);
        }
    }

    board->notifyObserver();

    solutionid++;
}


void MainWindow::on_pushSave_clicked()
{
    QFile file("board.txt");
    if(!file.open(QIODevice::WriteOnly)){
        qCritical() << file.errorString();
    }else{

        QTextStream stream(&file);
        stream<<board->robots.at(0)<< " ababbabbaba";
        file.close();
    }
}

