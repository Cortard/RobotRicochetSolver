#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>

#include <QGuiApplication>
#include <QScreen>
#include <QtGlobal>
#include <QTime>
#include "socketconnection.h"
#include <QThread>
#include <QFile>
#include <iostream>

using namespace std;

#include <QFontDatabase>
#include <iostream>

MainWindow::MainWindow(QWidget *parent, Board* bd)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      board(bd)
{
    ui->setupUi(this);

    connect(ui->AddObj, SIGNAL(clicked()), this, SLOT(onAddObjectivesButtonClick()));
    connect(ui->AddRbt, SIGNAL(clicked()), this, SLOT(onAddRobotButtonClick()));
    connect(ui->BtnCharger, SIGNAL(clicked()), this, SLOT(onLoadButtonClick()));
    connect(ui->ModeCharger, SIGNAL(clicked()), this, SLOT(onLoadModeButtonClick()));
    connect(ui->ModeCreer, SIGNAL(clicked()), this, SLOT(onCreateModeButtonClick()));
    connect(ui->ModeEdition, SIGNAL(clicked()), this, SLOT(onEditModeButtonClick()));
    connect(ui->ModeEntrainement, SIGNAL(clicked()), this, SLOT(onTrainModeButtonClick()));
    connect(ui->ModeHistoire, SIGNAL(clicked()), this, SLOT(onHistoryModeButtonClick()));
    connect(ui->ModeJouer, SIGNAL(clicked()), this, SLOT(onPlayModeButtonClick()));
    connect(ui->Jouer, SIGNAL(clicked()), this, SLOT(onPlayButtonClick()));
    connect(ui->JouerOfficiel, SIGNAL(clicked()), this, SLOT(onPlayOfficialButtonClick()));
    connect(ui->ModeOfficiel, SIGNAL(clicked()), this, SLOT(onOfficialModeButtonClick()));
    connect(ui->ModeLibre, SIGNAL(clicked()), this, SLOT(onFreeModeButtonClick()));
    connect(ui->ModeParametre, SIGNAL(clicked()), this, SLOT(onSettingsModeButtonClick()));
    connect(ui->GenererAleatoire, SIGNAL(clicked()), this, SLOT(onGenerateButtonClick()));
    connect(ui->Home, SIGNAL(clicked()), this, SLOT(onHomeButtonClick()));
    connect(ui->Rejouer, SIGNAL(clicked()), this, SLOT(onPlayAgainButtonClick()));
    connect(ui->Sauvegarder, SIGNAL(clicked()), this, SLOT(onSaveButtonClick()));
    connect(ui->resetPlateau, SIGNAL(clicked()), this, SLOT(onResetButtonClick()));
    connect(ui->Solution, SIGNAL(clicked()), this, SLOT(onSolveButtonClick()));
    connect(ui->Histoire1, SIGNAL(clicked()), this, SLOT(onHistory1ButtonClick()));
    connect(ui->Histoire2, SIGNAL(clicked()), this, SLOT(onHistory2ButtonClick()));
    connect(ui->Histoire3, SIGNAL(clicked()), this, SLOT(onHistory3ButtonClick()));
    connect(ui->Histoire4, SIGNAL(clicked()), this, SLOT(onHistory4ButtonClick()));
    connect(ui->Histoire5, SIGNAL(clicked()), this, SLOT(onHistory5ButtonClick()));
    connect(ui->Histoire6, SIGNAL(clicked()), this, SLOT(onHistory6ButtonClick()));
    connect(ui->Histoire7, SIGNAL(clicked()), this, SLOT(onHistory7ButtonClick()));
    connect(ui->Histoire8, SIGNAL(clicked()), this, SLOT(onHistory8ButtonClick()));

    ui->radioButton->setChecked(true);

    viewBoard = nullptr;
    viewPlato = nullptr;
    viewPlateauOfficiel = nullptr;

    QFont font = QFont("Poppins", 20);

    ui->stackedWidget->setFont(font);

    QList<QPushButton *> allBt = ui->stackedWidget->findChildren<QPushButton *>();
    for(QPushButton * button : allBt){
        button->setFont(font);
    }

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    move((screenGeometry.width() - width()) / 2, (screenGeometry.height() - height()) / 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleMovement() {
    board->mouvement++;
    ui->label->setText(QString::number(board->mouvement));
}

void MainWindow::onPlayModeButtonClick()
{
    ui->stackedWidget->setCurrentWidget(ui->pagejouer);
}

void MainWindow::onHistoryModeButtonClick()
{
    if(board->victoireHistoire>=2){
        ui->Histoire2->setStyleSheet("#Histoire2{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 	rgba(255, 255, 255, 107));border: 1px solid rgb(255, 255, 255);border-radius: 40px;padding:10px;color : rgb(255, 255, 255);}#Histoire2:hover {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));}#Histoire2:pressed {background-color: #9c2579;}");
    }
    if(board->victoireHistoire>=3){
        ui->Histoire3->setStyleSheet("#Histoire3{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 	rgba(255, 255, 255, 107));border: 1px solid rgb(255, 255, 255);border-radius: 40px;padding:10px;color : rgb(255, 255, 255);}#Histoire2:hover {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));}#Histoire2:pressed {background-color: #9c2579;}");
    }
    if(board->victoireHistoire>=4){
        ui->Histoire4->setStyleSheet("#Histoire4{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 	rgba(255, 255, 255, 107));border: 1px solid rgb(255, 255, 255);border-radius: 40px;padding:10px;color : rgb(255, 255, 255);}#Histoire2:hover {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));}#Histoire2:pressed {background-color: #9c2579;}");
    }
    if(board->victoireHistoire>=5){
        ui->Histoire4->setStyleSheet("#Histoire5{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 	rgba(255, 255, 255, 107));border: 1px solid rgb(255, 255, 255);border-radius: 40px;padding:10px;color : rgb(255, 255, 255);}#Histoire2:hover {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));}#Histoire2:pressed {background-color: #9c2579;}");
    }
    if(board->victoireHistoire>=6){
        ui->Histoire4->setStyleSheet("#Histoire6{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 	rgba(255, 255, 255, 107));border: 1px solid rgb(255, 255, 255);border-radius: 40px;padding:10px;color : rgb(255, 255, 255);}#Histoire2:hover {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));}#Histoire2:pressed {background-color: #9c2579;}");
    }
    if(board->victoireHistoire>=7){
        ui->Histoire4->setStyleSheet("#Histoire7{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 	rgba(255, 255, 255, 107));border: 1px solid rgb(255, 255, 255);border-radius: 40px;padding:10px;color : rgb(255, 255, 255);}#Histoire2:hover {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));}#Histoire2:pressed {background-color: #9c2579;}");
    }
    if(board->victoireHistoire>=8){
        ui->Histoire4->setStyleSheet("#Histoire8{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 	rgba(255, 255, 255, 107));border: 1px solid rgb(255, 255, 255);border-radius: 40px;padding:10px;color : rgb(255, 255, 255);}#Histoire2:hover {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));}#Histoire2:pressed {background-color: #9c2579;}");
    }
    ui->stackedWidget->setCurrentWidget(ui->pagehistoire);
}

void MainWindow::onTrainModeButtonClick()
{
    ui->stackedWidget->setCurrentWidget(ui->pagetrain);
}

void MainWindow::onAddObjectivesButtonClick()
{
    if (board->objectives.find(16) != board->objectives.end() && board->objectives[16] != -1) {
        return;
    }
    for (const auto& pair : board->objectives) {
        if (pair.second == 135) {
            return;
        }
    }
    ControllerAddObj(board).control();
}

void MainWindow::onEditModeButtonClick()
{
    ui->stackedWidget->setCurrentWidget(ui->edition);
}

void MainWindow::onAddRobotButtonClick()
{
    if (board->robots_move.find(4) != board->robots_move.end() && board->robots_move[4] != -1) {
        return;
    }
    for (const auto& pair : board->robots_move) {
        std::cout << "Robot ID : " << pair.first << ", Position : " << pair.second << std::endl;
        if (pair.second == 136) {
            return;
        }
    }
    ControllerAddRobot(board).control();
}

void MainWindow::onCreateModeButtonClick()
{
    ui->stackedWidget->setCurrentWidget(ui->choixplateau);
}

void MainWindow::onPlayButtonClick()
{
    if(board->objJeu!=-1){
        createViewPlato(6);
        solutionid=0;
        if(SocketConnection::getSolution(board)==1){
            flagRecu = 1;
        }
        board->robots_initial=board->robots_move;
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onFreeModeButtonClick()
{
    createViewBoard(1);
    ui->stackedWidget->setCurrentWidget(ui->pageplateau);
}

void MainWindow::onOfficialModeButtonClick()
{
    board->reset();
    viewPlateauOfficiel = nullptr;
    if (viewPlateauOfficiel == nullptr) {
        viewPlateauOfficiel = new ViewPlateauOfficiel(board);
        ui->stackedWidget->widget(8)->findChild<QGraphicsView*>()->setScene(viewPlateauOfficiel);
        viewPlateauOfficiel->setParent(ui->stackedWidget->widget(8)->findChild<QGraphicsView*>());
    }
    ui->stackedWidget->setCurrentWidget(ui->plateauofficiel);
}

void MainWindow::onPlayOfficialButtonClick()
{
    createViewBoard(1);
    ui->stackedWidget->setCurrentWidget(ui->pageplateau);
}

//TODO compatible generation
void MainWindow::onGenerateButtonClick()
{
    if(ui->radioButton->isChecked()){

        board->reset();

        int rand1 = rand() % 8;
        srand(QTime::currentTime().msec()+rand1);

        int randrb1 = rand() % 255;
        srand(QTime::currentTime().msec()+randrb1);
        while(randrb1==119 || randrb1==120 || randrb1==136 || randrb1==135){
            randrb1 = rand() % 255;
            srand(QTime::currentTime().msec()+randrb1);
        }
        int randrb2 = rand() % 255;
        srand(QTime::currentTime().msec()+randrb2);
        while(randrb2==119 || randrb2==120 || randrb2==136 || randrb2==135){
            randrb2 = rand() % 255;
            srand(QTime::currentTime().msec()+randrb2);
        }
        int randrb3 = rand() % 255;
        srand(QTime::currentTime().msec()+randrb3);
        while(randrb3==119 || randrb3==120 || randrb3==136 || randrb3==135){
            randrb3 = rand() % 255;
            srand(QTime::currentTime().msec()+randrb3);
        }
        int randrb4 = rand() % 255;
        srand(QTime::currentTime().msec()+randrb4);
        while(randrb4==119 || randrb4==120 || randrb4==136 || randrb4==135){
            randrb4 = rand() % 255;
            srand(QTime::currentTime().msec()+randrb4);
        }

        int randobj = rand() % 16;
        srand(QTime::currentTime().msec()+randobj);
        board->objJeu=randobj;

        board->robots_move.at(0)=randrb1;
        board->robots_move.at(1)=randrb2;
        board->robots_move.at(2)=randrb3;
        board->robots_move.at(3)=randrb4;

        switch (rand1) {
        case 0:
            board->constructPart1(this->board, 0);
            board->constructPart2(this->board, 1);
            board->constructPart4(this->board, 2);
            board->constructPart9(this->board, 3);
            break;
        case 1:
            board->constructPart16(this->board, 0);
            board->constructPart8(this->board, 1);
            board->constructPart6(this->board, 2);
            board->constructPart1(this->board, 3);
            break;
        case 2:
            board->constructPart10(this->board, 0);
            board->constructPart11(this->board, 1);
            board->constructPart12(this->board, 2);
            board->constructPart7(this->board, 3);
            break;
        case 3:
            board->constructPart14(this->board, 0);
            board->constructPart11(this->board, 1);
            board->constructPart13(this->board, 2);
            board->constructPart1(this->board, 3);
            break;
        case 4:
            board->constructPart14(this->board, 0);
            board->constructPart3(this->board, 1);
            board->constructPart4(this->board, 2);
            board->constructPart15(this->board, 3);
            break;
        case 5:
            board->constructPart9(this->board, 0);
            board->constructPart8(this->board, 1);
            board->constructPart6(this->board, 2);
            board->constructPart7(this->board, 3);
            break;
        case 6:
            board->constructPart2(this->board, 0);
            board->constructPart11(this->board, 1);
            board->constructPart3(this->board, 2);
            board->constructPart13(this->board, 3);
            break;
        case 7:
            board->constructPart2(this->board, 0);
            board->constructPart7(this->board, 1);
            board->constructPart10(this->board, 2);
            board->constructPart16(this->board, 3);
            break;
        }
        createViewPlato(6);
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onHistory1ButtonClick()
{

    std::cout<<"1"<<std::endl;
    solutionid=0;
    std::cout<<"1.5"<<std::endl;
    this->board->reset();
    std::cout<<"2"<<std::endl;
    board->constructPart13(this->board, 0);
    board->constructPart15(this->board, 1);
    board->constructPart2(this->board, 2);
    board->constructPart3(this->board, 3);
    std::cout<<"3"<<std::endl;
    this->board->addRobot(0,2);
    this->board->addRobot(1,250);
    this->board->addRobot(2,55);
    this->board->addRobot(3,86);
    this->board->objJeu=0;
    std::cout<<"4"<<std::endl;

    //TODO async
    if(SocketConnection::getSolution(board)==1){
        flagRecu = 1;
    }
    this->board->robots_initial=this->board->robots_move;

    std::cout<<"5"<<std::endl;
    createViewPlato(6);
    ui->stackedWidget->setCurrentWidget(ui->plateau);
    std::cout<<"6"<<std::endl;
}

void MainWindow::onHistory2ButtonClick()
{
    if(board->victoireHistoire>=2){
        solutionid=0;
        this->board->reset();
        board->constructPart13(this->board, 0);
        board->constructPart15(this->board, 1);
        board->constructPart2(this->board, 2);
        board->constructPart3(this->board, 3);
        this->board->addRobot(0,2);
        this->board->addRobot(1,250);
        this->board->addRobot(2,55);
        this->board->addRobot(3,86);
        this->board->objJeu=0;

        if(SocketConnection::getSolution(board)==1){
            flagRecu = 1;
        }
        this->board->robots_initial=this->board->robots_move;

        createViewPlato(6);
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onHistory3ButtonClick()
{
    if(board->victoireHistoire>=3){
        solutionid=0;
        this->board->reset();
        board->constructPart13(this->board, 0);
        board->constructPart15(this->board, 1);
        board->constructPart2(this->board, 2);
        board->constructPart3(this->board, 3);
        this->board->addRobot(0,2);
        this->board->addRobot(1,250);
        this->board->addRobot(2,55);
        this->board->addRobot(3,86);
        this->board->objJeu=0;

        if(SocketConnection::getSolution(board)==1){
            flagRecu = 1;
        }
        this->board->robots_initial=this->board->robots_move;

        createViewPlato(6);
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onHistory4ButtonClick()
{
    if(board->victoireHistoire>=4){
        solutionid=0;
        this->board->reset();
        board->constructPart13(this->board, 0);
        board->constructPart15(this->board, 1);
        board->constructPart2(this->board, 2);
        board->constructPart3(this->board, 3);
        this->board->addRobot(0,2);
        this->board->addRobot(1,250);
        this->board->addRobot(2,55);
        this->board->addRobot(3,86);
        this->board->objJeu=0;

        if(SocketConnection::getSolution(board)==1){
            flagRecu = 1;
        }
        this->board->robots_initial=this->board->robots_move;

        createViewPlato(6);
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onHistory5ButtonClick()
{
    if(board->victoireHistoire>=5){
        solutionid=0;
        this->board->reset();
        board->constructPart13(this->board, 0);
        board->constructPart15(this->board, 1);
        board->constructPart2(this->board, 2);
        board->constructPart3(this->board, 3);
        this->board->addRobot(0,2);
        this->board->addRobot(1,250);
        this->board->addRobot(2,55);
        this->board->addRobot(3,86);
        this->board->objJeu=0;

        if(SocketConnection::getSolution(board)==1){
            flagRecu = 1;
        }
        this->board->robots_initial=this->board->robots_move;

        createViewPlato(6);
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onHistory6ButtonClick()
{
    if(board->victoireHistoire>=6){
        solutionid=0;
        this->board->reset();
        board->constructPart13(this->board, 0);
        board->constructPart15(this->board, 1);
        board->constructPart2(this->board, 2);
        board->constructPart3(this->board, 3);
        this->board->addRobot(0,2);
        this->board->addRobot(1,250);
        this->board->addRobot(2,55);
        this->board->addRobot(3,86);
        this->board->objJeu=0;

        if(SocketConnection::getSolution(board)==1){
            flagRecu = 1;
        }
        this->board->robots_initial=this->board->robots_move;

        createViewPlato(6);
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onHistory7ButtonClick()
{
    if(board->victoireHistoire>=7){
        solutionid=0;
        this->board->reset();
        board->constructPart13(this->board, 0);
        board->constructPart15(this->board, 1);
        board->constructPart2(this->board, 2);
        board->constructPart3(this->board, 3);
        this->board->addRobot(0,2);
        this->board->addRobot(1,250);
        this->board->addRobot(2,55);
        this->board->addRobot(3,86);
        this->board->objJeu=0;

        if(SocketConnection::getSolution(board)==1){
            flagRecu = 1;
        }
        this->board->robots_initial=this->board->robots_move;

        createViewPlato(6);
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onHistory8ButtonClick()
{
    if(board->victoireHistoire>=6){
        solutionid=0;
        this->board->reset();
        board->constructPart13(this->board, 0);
        board->constructPart15(this->board, 1);
        board->constructPart2(this->board, 2);
        board->constructPart3(this->board, 3);
        this->board->addRobot(0,2);
        this->board->addRobot(1,250);
        this->board->addRobot(2,55);
        this->board->addRobot(3,86);
        this->board->objJeu=0;

        if(SocketConnection::getSolution(board)==1){
            flagRecu = 1;
        }
        this->board->robots_initial=this->board->robots_move;

        createViewPlato(6);
        ui->stackedWidget->setCurrentWidget(ui->plateau);
    }
}

void MainWindow::onResetButtonClick()
{
    this->board->reset();
}

void MainWindow::onPlayAgainButtonClick()
{
    board->robots_move=board->robots_initial;
    solutionid=0;
    board->notifyObserver();
    createViewBoard(1);
    ui->stackedWidget->setCurrentWidget(ui->pageplateau);
}

void MainWindow::onSolveButtonClick()
{
    if(flagRecu == 1){
        return;
    }

    if(solutionid==0){
        board->robots_move=board->robots_initial;
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

    int col = board->robots_move.at(rbt) % 16;
    int row = board->robots_move.at(rbt) / 16;

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
            auto it = std::find_if(board->robots_move.begin(), board->robots_move.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });
            if (it != board->robots_move.end()){
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

            auto it = std::find_if(board->robots_move.begin(), board->robots_move.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });
            if (it != board->robots_move.end()){
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
            auto it = std::find_if(board->robots_move.begin(), board->robots_move.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });
            if (it != board->robots_move.end()){
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
            auto it = std::find_if(board->robots_move.begin(), board->robots_move.end(),
                                   [pos](const auto& pair) { return pair.second == pos; });
            if (it != board->robots_move.end()){
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

void MainWindow::onSaveButtonClick()
{
    QFile file("board.txt");
    if(!file.open(QIODevice::Append)){
        qCritical() << file.errorString();
    }else{

        QTextStream stream(&file);

        stream<< "plateau "<<fichier << " ";

        for(int i=0;i<5;i++){
            stream<<board->robots_initial.at(i) << " ";
        }
        for(int i=0;i<17;i++){
            stream<<board->objectives.at(i) << " " ;
        }
        stream<<board->objJeu << " " ;
        for(int i=0;i<256;i++){
            if(HAS_WALL(board->cases[i],NORTH)==1){
                wall+=1;
            }
            if(HAS_WALL(board->cases[i],EAST)==2){
                wall+=2;
            }
            if(HAS_WALL(board->cases[i],SOUTH)==4){
                wall+=4;
            }
            if(HAS_WALL(board->cases[i],WEST)==8){
                wall+=8;
            }
            stream<<wall << " " ;
            wall=0;
        }

        stream << "\n";
        fichier++;
        file.close();
    }
}

void MainWindow::onLoadModeButtonClick()
{
    QFile file("board.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << file.errorString();
    } else {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" ");

            if (parts.size() >= 2 && parts[0] == "plateau" && pass==true) {
                QString fichier = parts[1];
                ui->stackedWidget->widget(9)->findChild<QListWidget*>()->addItem("Plateau " + fichier);
            }
        }

        file.close();
    }
    pass = false;
    ui->stackedWidget->setCurrentWidget(ui->pagecharger);
}

void MainWindow::onLoadButtonClick()
{
    if(ui->stackedWidget->widget(9)->findChild<QListWidget*>()->currentItem()!=0){
        QString selectedTex = ui->stackedWidget->widget(9)->findChild<QListWidget*>()->currentItem()->text();
        QStringList part = selectedTex.split(" ");
        QString fichier = part[1];
        qDebug() << fichier;
        QFile file("board.txt");

        if (!file.open(QIODevice::ReadOnly)) {
            qCritical() << file.errorString();
        } else {        QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(" ");

                if (part[1]==parts[1]){

                    board->reset();
                    for(int i=0;i<5;i++){
                        board->robots_move.at(i)=parts[i + 2].toInt();
                    }
                    for(int i=0;i<17;i++){
                        board->objectives.at(i)=parts[i + 7].toInt();
                    }
                    for(int i=0;i<256;i++){
                        if(parts[i + 24].toInt()>=8){
                            SET_WALL(board->cases[i-1],WEST);
                        }
                        if((parts[i + 24].toInt()>=4 && parts[i + 24].toInt()<=7) || parts[i + 24].toInt()>=12){
                            SET_WALL(board->cases[i-1],SOUTH);
                        }
                        if(parts[i + 24].toInt()==2 || parts[i + 24].toInt()==3 || parts[i + 24].toInt()==6 || parts[i + 24].toInt()==7 || parts[i + 24].toInt()==10 || parts[i + 24].toInt()==11 || parts[i + 24].toInt()>=14){
                            SET_WALL(board->cases[i-1],EAST);
                        }
                        if(parts[i + 24].toInt()%2==1){
                            SET_WALL(board->cases[i-1],NORTH);
                        }
                    }
                    board->objJeu=parts[24].toInt();
                    createViewBoard(1);
                }
            }

            file.close();
        }
    }
}

void MainWindow::onHomeButtonClick()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenuwindow);
}

void MainWindow::onSettingsModeButtonClick()
{
    ui->stackedWidget->setCurrentWidget(ui->utilisation);
}

void MainWindow::createViewPlato(int widget) {
    if (viewPlato == nullptr) {
        viewPlato = new viewPlateau(board);
        ui->stackedWidget->widget(widget)->findChild<QGraphicsView*>()->setScene(viewPlato);
        viewPlato->setParent(ui->stackedWidget->widget(widget)->findChild<QGraphicsView*>());
        connect(viewPlato, &viewPlateau::movementOccurred, this, &MainWindow::handleMovement);
    }else{
        delete viewPlato;
        viewPlato = new viewPlateau(board);
        ui->stackedWidget->widget(widget)->findChild<QGraphicsView*>()->setScene(viewPlato);
        viewPlato->setParent(ui->stackedWidget->widget(widget)->findChild<QGraphicsView*>());
        connect(viewPlato, &viewPlateau::movementOccurred, this, &MainWindow::handleMovement);
    }
}

void MainWindow::createViewBoard(int widget) {
    if(viewBoard==nullptr){
        viewBoard = new ViewBoard(board);
        ui->stackedWidget->widget(widget)->findChild<QGraphicsView*>()->setScene(viewBoard);
        viewBoard->setParent(ui->stackedWidget->widget(widget)->findChild<QGraphicsView*>());
        ui->stackedWidget->setCurrentWidget(ui->pageplateau);
    }else{
        delete viewBoard;
        viewBoard = new ViewBoard(board);
        ui->stackedWidget->widget(widget)->findChild<QGraphicsView*>()->setScene(viewBoard);
        viewBoard->setParent(ui->stackedWidget->widget(widget)->findChild<QGraphicsView*>());
        ui->stackedWidget->setCurrentWidget(ui->pageplateau);
    }
}
