/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QStackedWidget *stackedWidget;
    QWidget *mainmenuwindow;
    QWidget *widget_3;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_11;
    QVBoxLayout *verticalLayout_10;
    QFrame *frame_3;
    QFrame *frame_2;
    QPushButton *ModeJouer;
    QPushButton *ModeEdition;
    QPushButton *ModeParametre;
    QWidget *pageplateau;
    QWidget *verticalLayoutWidget_4;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QFrame *frame_4;
    QPushButton *AddRbt;
    QPushButton *AddObj;
    QPushButton *Jouer;
    QGraphicsView *graphicsView_2;
    QPushButton *resetPlateau;
    QWidget *pagehistoire;
    QPushButton *Histoire1;
    QPushButton *Histoire2;
    QWidget *verticalLayoutWidget_2;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QPushButton *Histoire3;
    QPushButton *Histoire4;
    QPushButton *Histoire5;
    QPushButton *Histoire6;
    QPushButton *Histoire7;
    QPushButton *Histoire8;
    QWidget *pagetrain;
    QWidget *verticalLayoutWidget_3;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_2;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QPushButton *GenererAleatoire;
    QLabel *label_6;
    QWidget *pagejouer;
    QWidget *verticalLayoutWidget_7;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *ModeHistoire;
    QPushButton *ModeEntrainement;
    QFrame *frame_10;
    QWidget *edition;
    QWidget *verticalLayoutWidget_5;
    QGridLayout *gridLayout_4;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *ModeCharger;
    QPushButton *ModeCreer;
    QWidget *plateau;
    QWidget *verticalLayoutWidget_6;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_7;
    QPushButton *Rejouer;
    QLabel *label;
    QPushButton *Solution;
    QPushButton *Sauvegarder;
    QGraphicsView *graphicsView_4;
    QWidget *choixplateau;
    QWidget *verticalLayoutWidget_9;
    QGridLayout *gridLayout_14;
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *ModeOfficiel;
    QPushButton *ModeLibre;
    QWidget *plateauofficiel;
    QWidget *verticalLayoutWidget_8;
    QGridLayout *gridLayout_10;
    QPushButton *JouerOfficiel;
    QHBoxLayout *horizontalLayout_8;
    QGraphicsView *graphicsView_6;
    QWidget *pagecharger;
    QWidget *verticalLayoutWidget_10;
    QGridLayout *gridLayout_12;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_5;
    QPushButton *BtnCharger;
    QListWidget *listWidget_2;
    QWidget *utilisation;
    QFrame *frame_19;
    QPushButton *Home;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1304, 632);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-10, -10, 1321, 741));
        frame->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/lac.jpg) center center;\n"
""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 1311, 631));
        stackedWidget->setStyleSheet(QString::fromUtf8("background:none;"));
        mainmenuwindow = new QWidget();
        mainmenuwindow->setObjectName("mainmenuwindow");
        widget_3 = new QWidget(mainmenuwindow);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(0, 0, 1301, 631));
        gridLayoutWidget_2 = new QWidget(widget_3);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 1311, 736));
        gridLayout_11 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_11->setObjectName("gridLayout_11");
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_10->setContentsMargins(320, 50, 320, 200);
        frame_3 = new QFrame(gridLayoutWidget_2);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(0, 150));
        frame_3->setMaximumSize(QSize(16777215, 150));
        frame_3->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/nom.png) center center no-repeat;\n"
"border:none;"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);

        verticalLayout_10->addWidget(frame_3);

        frame_2 = new QFrame(gridLayoutWidget_2);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("border:none;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        ModeJouer = new QPushButton(frame_2);
        ModeJouer->setObjectName("ModeJouer");
        ModeJouer->setGeometry(QRect(50, 50, 571, 71));
        ModeJouer->setMaximumSize(QSize(666666, 100));
        QFont font;
        font.setFamilies({QString::fromUtf8("Poppins-Regular")});
        font.setPointSize(36);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        ModeJouer->setFont(font);
        ModeJouer->setCursor(QCursor(Qt::PointingHandCursor));
        ModeJouer->setStyleSheet(QString::fromUtf8("QPushButton#ModeJouer {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"	font:(\"Poppins\",50);\n"
"}\n"
"\n"
"QPushButton#ModeJouer:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"QPushButton#ModeJouer:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        ModeEdition = new QPushButton(frame_2);
        ModeEdition->setObjectName("ModeEdition");
        ModeEdition->setGeometry(QRect(50, 150, 571, 71));
        ModeEdition->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe Print")});
        font1.setPointSize(36);
        font1.setBold(true);
        ModeEdition->setFont(font1);
        ModeEdition->setStyleSheet(QString::fromUtf8("#ModeEdition {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 107));\n"
"    border: 1px solid rgb(255, 255, 255);\n"
"    border-radius: 25px;\n"
"    padding: 10px;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"#ModeEdition:hover {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));\n"
"    /* Ajouter un effet de flou pour le survol */\n"
"    border: 1px solid rgba(255, 255, 255, 0.5);\n"
"}\n"
"\n"
"#ModeEdition:pressed {\n"
"    background-color: #9c2579;\n"
"}\n"
""));
        ModeParametre = new QPushButton(frame_2);
        ModeParametre->setObjectName("ModeParametre");
        ModeParametre->setGeometry(QRect(48, 249, 571, 71));
        ModeParametre->setMaximumSize(QSize(16777215, 100));
        ModeParametre->setFont(font1);
        ModeParametre->setStyleSheet(QString::fromUtf8("#ModeParametre {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 107));\n"
"    border: 1px solid rgb(255, 255, 255);\n"
"    border-radius: 25px;\n"
"    padding: 10px;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"#ModeParametre:hover {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 rgba(255, 255, 255, 150));\n"
"    border: 1px solid rgba(255, 255, 255, 0.5);\n"
"}\n"
"\n"
"#ModeParametre:pressed {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
""));

        verticalLayout_10->addWidget(frame_2);


        gridLayout_11->addLayout(verticalLayout_10, 0, 0, 1, 1);

        stackedWidget->addWidget(mainmenuwindow);
        pageplateau = new QWidget();
        pageplateau->setObjectName("pageplateau");
        verticalLayoutWidget_4 = new QWidget(pageplateau);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(10, 10, 1261, 607));
        gridLayout_6 = new QGridLayout(verticalLayoutWidget_4);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(100, 100, 100, 100);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(100);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(100, -1, 100, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        frame_4 = new QFrame(verticalLayoutWidget_4);
        frame_4->setObjectName("frame_4");
        frame_4->setStyleSheet(QString::fromUtf8("border:none;"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        AddRbt = new QPushButton(frame_4);
        AddRbt->setObjectName("AddRbt");
        AddRbt->setGeometry(QRect(70, 110, 200, 41));
        AddRbt->setMinimumSize(QSize(200, 0));
        AddRbt->setMaximumSize(QSize(200, 100));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font2.setPointSize(15);
        AddRbt->setFont(font2);
        AddRbt->setStyleSheet(QString::fromUtf8("QPushButton#AddRbt {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#AddRbt:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#AddRbt:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        AddObj = new QPushButton(frame_4);
        AddObj->setObjectName("AddObj");
        AddObj->setGeometry(QRect(70, 200, 200, 41));
        AddObj->setMinimumSize(QSize(200, 0));
        AddObj->setMaximumSize(QSize(200, 100));
        AddObj->setFont(font2);
        AddObj->setStyleSheet(QString::fromUtf8("QPushButton#AddObj {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#AddObj:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#AddObj:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        Jouer = new QPushButton(frame_4);
        Jouer->setObjectName("Jouer");
        Jouer->setGeometry(QRect(70, 290, 200, 41));
        Jouer->setMinimumSize(QSize(200, 0));
        Jouer->setMaximumSize(QSize(200, 100));
        Jouer->setFont(font2);
        Jouer->setStyleSheet(QString::fromUtf8("QPushButton#Jouer {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#Jouer:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#Jouer:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        verticalLayout->addWidget(frame_4);


        horizontalLayout_4->addLayout(verticalLayout);

        graphicsView_2 = new QGraphicsView(verticalLayoutWidget_4);
        graphicsView_2->setObjectName("graphicsView_2");
        graphicsView_2->setMinimumSize(QSize(405, 405));
        graphicsView_2->setMaximumSize(QSize(405, 405));
        graphicsView_2->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/fond.png) center center;"));

        horizontalLayout_4->addWidget(graphicsView_2);


        gridLayout_6->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        resetPlateau = new QPushButton(pageplateau);
        resetPlateau->setObjectName("resetPlateau");
        resetPlateau->setGeometry(QRect(1070, 450, 50, 50));
        resetPlateau->setMinimumSize(QSize(50, 50));
        resetPlateau->setMaximumSize(QSize(50, 50));
        resetPlateau->setStyleSheet(QString::fromUtf8("QPushButton#resetPlateau {\n"
"    background : url(:/img/Img/reset.png) center center no-repeat;\n"
"	border:none;\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#resetPlateau:hover {\n"
"    background-color: #9c2579;\n"
"}"));
        stackedWidget->addWidget(pageplateau);
        pagehistoire = new QWidget();
        pagehistoire->setObjectName("pagehistoire");
        Histoire1 = new QPushButton(pagehistoire);
        Histoire1->setObjectName("Histoire1");
        Histoire1->setGeometry(QRect(120, 200, 80, 80));
        Histoire1->setMinimumSize(QSize(80, 80));
        Histoire1->setMaximumSize(QSize(70, 70));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        Histoire1->setFont(font3);
        Histoire1->setStyleSheet(QString::fromUtf8("#Histoire1{\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 40px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#Histoire1:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#Histoire1:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        Histoire2 = new QPushButton(pagehistoire);
        Histoire2->setObjectName("Histoire2");
        Histoire2->setGeometry(QRect(260, 260, 80, 80));
        Histoire2->setMinimumSize(QSize(80, 80));
        Histoire2->setMaximumSize(QSize(70, 70));
        Histoire2->setFont(font3);
        Histoire2->setStyleSheet(QString::fromUtf8("#Histoire2{\n"
"	background : url(:/img/Img/cadena.png) center center no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 40px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#Histoire2:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#Histoire2:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        verticalLayoutWidget_2 = new QWidget(pagehistoire);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 1261, 701));
        gridLayout_5 = new QGridLayout(verticalLayoutWidget_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(100, 0, 100, 500);
        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName("label_4");
        QFont font4;
        font4.setPointSize(30);
        font4.setBold(true);
        label_4->setFont(font4);
        label_4->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/histoire.png) center center no-repeat;\n"
"border:none;"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_4, 1, 0, 1, 1);

        Histoire3 = new QPushButton(pagehistoire);
        Histoire3->setObjectName("Histoire3");
        Histoire3->setGeometry(QRect(400, 210, 80, 80));
        Histoire3->setMinimumSize(QSize(80, 80));
        Histoire3->setMaximumSize(QSize(70, 70));
        Histoire3->setFont(font3);
        Histoire3->setStyleSheet(QString::fromUtf8("#Histoire3 {\n"
"	background : url(:/img/Img/cadena.png) center center no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 40px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#Histoire3:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#Histoire3:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        Histoire4 = new QPushButton(pagehistoire);
        Histoire4->setObjectName("Histoire4");
        Histoire4->setGeometry(QRect(540, 290, 80, 80));
        Histoire4->setMinimumSize(QSize(80, 80));
        Histoire4->setMaximumSize(QSize(70, 70));
        Histoire4->setFont(font3);
        Histoire4->setStyleSheet(QString::fromUtf8("#Histoire4 {\n"
"	background : url(:/img/Img/cadena.png) center center no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 40px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#Histoire4:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#Histoire4:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        Histoire5 = new QPushButton(pagehistoire);
        Histoire5->setObjectName("Histoire5");
        Histoire5->setGeometry(QRect(600, 400, 80, 80));
        Histoire5->setMinimumSize(QSize(80, 80));
        Histoire5->setMaximumSize(QSize(70, 70));
        Histoire5->setFont(font3);
        Histoire5->setStyleSheet(QString::fromUtf8("#Histoire5 {\n"
"	background : url(:/img/Img/cadena.png) center center no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 40px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#Histoire5:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#Histoire5:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        Histoire6 = new QPushButton(pagehistoire);
        Histoire6->setObjectName("Histoire6");
        Histoire6->setGeometry(QRect(740, 490, 80, 80));
        Histoire6->setMinimumSize(QSize(80, 80));
        Histoire6->setMaximumSize(QSize(70, 70));
        Histoire6->setFont(font3);
        Histoire6->setStyleSheet(QString::fromUtf8("#Histoire6 {\n"
"	background : url(:/img/Img/cadena.png) center center no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 40px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#Histoire6:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#Histoire6:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        Histoire7 = new QPushButton(pagehistoire);
        Histoire7->setObjectName("Histoire7");
        Histoire7->setGeometry(QRect(880, 360, 80, 80));
        Histoire7->setMinimumSize(QSize(80, 80));
        Histoire7->setMaximumSize(QSize(70, 70));
        Histoire7->setFont(font3);
        Histoire7->setStyleSheet(QString::fromUtf8("#Histoire7 {\n"
"	background : url(:/img/Img/cadena.png) center center no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 40px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#Histoire7:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#Histoire7:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        Histoire8 = new QPushButton(pagehistoire);
        Histoire8->setObjectName("Histoire8");
        Histoire8->setGeometry(QRect(1010, 440, 80, 80));
        Histoire8->setMinimumSize(QSize(80, 80));
        Histoire8->setMaximumSize(QSize(70, 70));
        Histoire8->setFont(font3);
        Histoire8->setStyleSheet(QString::fromUtf8("#Histoire8 {\n"
"	background : url(:/img/Img/cadena.png) center center no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 40px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#Histoire8:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#Histoire8:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        stackedWidget->addWidget(pagehistoire);
        verticalLayoutWidget_2->raise();
        Histoire2->raise();
        Histoire1->raise();
        Histoire3->raise();
        Histoire4->raise();
        Histoire5->raise();
        Histoire6->raise();
        Histoire7->raise();
        Histoire8->raise();
        pagetrain = new QWidget();
        pagetrain->setObjectName("pagetrain");
        verticalLayoutWidget_3 = new QWidget(pagetrain);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 1281, 611));
        gridLayout_7 = new QGridLayout(verticalLayoutWidget_3);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(100, 0, 100, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(150);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(100, -1, 100, -1);
        widget_2 = new QWidget(verticalLayoutWidget_3);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8(""));
        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(270, 60, 351, 261));
        groupBox_2->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: rgb(255, 255, 255);"));
        radioButton = new QRadioButton(groupBox_2);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(80, 30, 106, 22));
        radioButton_2 = new QRadioButton(groupBox_2);
        buttonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(80, 60, 106, 22));
        radioButton_3 = new QRadioButton(groupBox_2);
        buttonGroup->addButton(radioButton_3);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(80, 90, 106, 22));
        GenererAleatoire = new QPushButton(groupBox_2);
        GenererAleatoire->setObjectName("GenererAleatoire");
        GenererAleatoire->setGeometry(QRect(80, 130, 200, 50));
        GenererAleatoire->setMinimumSize(QSize(200, 50));
        GenererAleatoire->setMaximumSize(QSize(200, 50));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font5.setPointSize(20);
        font5.setBold(true);
        GenererAleatoire->setFont(font5);
        GenererAleatoire->setStyleSheet(QString::fromUtf8("QPushButton#GenererAleatoire {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#GenererAleatoire:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#GenererAleatoire:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        horizontalLayout_5->addWidget(widget_2);


        gridLayout_7->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        label_6 = new QLabel(verticalLayoutWidget_3);
        label_6->setObjectName("label_6");
        label_6->setMaximumSize(QSize(16777215, 150));
        label_6->setFont(font4);
        label_6->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/entrainement.png) center center no-repeat;\n"
"border:none;"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_6, 0, 0, 1, 1);

        stackedWidget->addWidget(pagetrain);
        pagejouer = new QWidget();
        pagejouer->setObjectName("pagejouer");
        pagejouer->setMinimumSize(QSize(1280, 720));
        pagejouer->setMaximumSize(QSize(1280, 720));
        verticalLayoutWidget_7 = new QWidget(pagejouer);
        verticalLayoutWidget_7->setObjectName("verticalLayoutWidget_7");
        verticalLayoutWidget_7->setGeometry(QRect(10, 10, 1261, 601));
        gridLayout_8 = new QGridLayout(verticalLayoutWidget_7);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_8->setContentsMargins(0, 0, 100, 0);
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(150);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalLayout_16->setContentsMargins(100, -1, 0, 50);
        ModeHistoire = new QPushButton(verticalLayoutWidget_7);
        ModeHistoire->setObjectName("ModeHistoire");
        ModeHistoire->setMinimumSize(QSize(350, 350));
        ModeHistoire->setMaximumSize(QSize(350, 350));
        ModeHistoire->setFont(font1);
        ModeHistoire->setStyleSheet(QString::fromUtf8("#ModeHistoire {\n"
"	background : url(:/img/Img/histoireicon.png) center cente no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#ModeHistoire:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#ModeHistoire:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        horizontalLayout_16->addWidget(ModeHistoire);

        ModeEntrainement = new QPushButton(verticalLayoutWidget_7);
        ModeEntrainement->setObjectName("ModeEntrainement");
        ModeEntrainement->setMinimumSize(QSize(350, 350));
        ModeEntrainement->setMaximumSize(QSize(350, 350));
        ModeEntrainement->setFont(font1);
        ModeEntrainement->setStyleSheet(QString::fromUtf8("#ModeEntrainement {\n"
"	background : url(:/img/Img/entrainementicon.png) center cente no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#ModeEntrainement:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#ModeEntrainement:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        horizontalLayout_16->addWidget(ModeEntrainement);


        gridLayout_8->addLayout(horizontalLayout_16, 2, 0, 1, 1);

        frame_10 = new QFrame(verticalLayoutWidget_7);
        frame_10->setObjectName("frame_10");
        frame_10->setMaximumSize(QSize(16777215, 100));
        frame_10->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/jouer.png) center center no-repeat;\n"
"margin-left:100px;\n"
"border:none;"));
        frame_10->setFrameShape(QFrame::StyledPanel);
        frame_10->setFrameShadow(QFrame::Raised);

        gridLayout_8->addWidget(frame_10, 1, 0, 1, 1);

        stackedWidget->addWidget(pagejouer);
        edition = new QWidget();
        edition->setObjectName("edition");
        verticalLayoutWidget_5 = new QWidget(edition);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(10, 10, 1261, 601));
        gridLayout_4 = new QGridLayout(verticalLayoutWidget_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 100, 0);
        frame_8 = new QFrame(verticalLayoutWidget_5);
        frame_8->setObjectName("frame_8");
        frame_8->setMaximumSize(QSize(16777215, 100));
        frame_8->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/edition.png) no-repeat;\n"
"margin-left:400px;\n"
"border:none;"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(frame_8, 1, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(150);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        horizontalLayout_14->setContentsMargins(100, -1, 0, 50);
        ModeCharger = new QPushButton(verticalLayoutWidget_5);
        ModeCharger->setObjectName("ModeCharger");
        ModeCharger->setMinimumSize(QSize(350, 350));
        ModeCharger->setMaximumSize(QSize(350, 350));
        ModeCharger->setFont(font1);
        ModeCharger->setStyleSheet(QString::fromUtf8("/*QPushButton#ModeCharger{\n"
"	background : url(:/img/Img/charger.png) center center;\n"
"	border:none;\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color:rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#ModeCharger:hover {\n"
"	color:rgb(194, 167, 225);\n"
"} */\n"
"\n"
"QPushButton#ModeCharger {\n"
"	background : url(:/img/Img/chargericon.png) center center;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#ModeCharger:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"QPushButton#ModeCharger:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
"\n"
"\n"
""));

        horizontalLayout_14->addWidget(ModeCharger);

        ModeCreer = new QPushButton(verticalLayoutWidget_5);
        ModeCreer->setObjectName("ModeCreer");
        ModeCreer->setMinimumSize(QSize(350, 350));
        ModeCreer->setMaximumSize(QSize(350, 350));
        ModeCreer->setFont(font1);
        ModeCreer->setStyleSheet(QString::fromUtf8("#ModeCreer {\n"
"	background : url(:/img/Img/creericon.png) center center no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#ModeCreer:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#ModeCreer:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        horizontalLayout_14->addWidget(ModeCreer);


        gridLayout_4->addLayout(horizontalLayout_14, 2, 0, 1, 1);

        stackedWidget->addWidget(edition);
        plateau = new QWidget();
        plateau->setObjectName("plateau");
        verticalLayoutWidget_6 = new QWidget(plateau);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(10, 10, 1261, 607));
        gridLayout_9 = new QGridLayout(verticalLayoutWidget_6);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(100, 100, 100, 100);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(100);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(100, -1, 100, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        frame_7 = new QFrame(verticalLayoutWidget_6);
        frame_7->setObjectName("frame_7");
        frame_7->setStyleSheet(QString::fromUtf8("border:none;"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        Rejouer = new QPushButton(frame_7);
        Rejouer->setObjectName("Rejouer");
        Rejouer->setGeometry(QRect(80, 220, 200, 41));
        Rejouer->setMinimumSize(QSize(200, 0));
        Rejouer->setMaximumSize(QSize(200, 100));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font6.setPointSize(15);
        font6.setBold(true);
        Rejouer->setFont(font6);
        Rejouer->setStyleSheet(QString::fromUtf8("QPushButton#Rejouer {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#Rejouer:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#Rejouer:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        label = new QLabel(frame_7);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 150, 31, 31));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font7.setPointSize(20);
        label->setFont(font7);
        Solution = new QPushButton(frame_7);
        Solution->setObjectName("Solution");
        Solution->setGeometry(QRect(80, 280, 200, 40));
        Solution->setMinimumSize(QSize(200, 40));
        Solution->setMaximumSize(QSize(200, 40));
        Solution->setFont(font6);
        Solution->setStyleSheet(QString::fromUtf8("QPushButton#Solution {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#Solution:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#Solution:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        Sauvegarder = new QPushButton(frame_7);
        Sauvegarder->setObjectName("Sauvegarder");
        Sauvegarder->setGeometry(QRect(80, 70, 200, 40));
        Sauvegarder->setMinimumSize(QSize(200, 40));
        Sauvegarder->setMaximumSize(QSize(200, 40));
        Sauvegarder->setFont(font6);
        Sauvegarder->setStyleSheet(QString::fromUtf8("QPushButton#Sauvegarder {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#Sauvegarder:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#Sauvegarder:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        verticalLayout_3->addWidget(frame_7);


        horizontalLayout_7->addLayout(verticalLayout_3);

        graphicsView_4 = new QGraphicsView(verticalLayoutWidget_6);
        graphicsView_4->setObjectName("graphicsView_4");
        graphicsView_4->setMinimumSize(QSize(405, 405));
        graphicsView_4->setMaximumSize(QSize(405, 405));
        graphicsView_4->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/fond.png) center center;"));

        horizontalLayout_7->addWidget(graphicsView_4);


        gridLayout_9->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        stackedWidget->addWidget(plateau);
        choixplateau = new QWidget();
        choixplateau->setObjectName("choixplateau");
        verticalLayoutWidget_9 = new QWidget(choixplateau);
        verticalLayoutWidget_9->setObjectName("verticalLayoutWidget_9");
        verticalLayoutWidget_9->setGeometry(QRect(10, 10, 1261, 601));
        gridLayout_14 = new QGridLayout(verticalLayoutWidget_9);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setObjectName("gridLayout_14");
        gridLayout_14->setContentsMargins(0, 0, 100, 0);
        frame_9 = new QFrame(verticalLayoutWidget_9);
        frame_9->setObjectName("frame_9");
        frame_9->setMaximumSize(QSize(16777215, 100));
        frame_9->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/edition.png) no-repeat;\n"
"margin-left:400px;\n"
"border:none;"));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);

        gridLayout_14->addWidget(frame_9, 1, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(150);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(100, -1, 0, 50);
        ModeOfficiel = new QPushButton(verticalLayoutWidget_9);
        ModeOfficiel->setObjectName("ModeOfficiel");
        ModeOfficiel->setMinimumSize(QSize(350, 350));
        ModeOfficiel->setMaximumSize(QSize(350, 350));
        ModeOfficiel->setFont(font1);
        ModeOfficiel->setStyleSheet(QString::fromUtf8("#ModeOfficiel{\n"
"	background : url(:/img/Img/officielicon.png) center cente no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#ModeOfficiel:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#ModeOfficiel:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        horizontalLayout_15->addWidget(ModeOfficiel);

        ModeLibre = new QPushButton(verticalLayoutWidget_9);
        ModeLibre->setObjectName("ModeLibre");
        ModeLibre->setMinimumSize(QSize(350, 350));
        ModeLibre->setMaximumSize(QSize(350, 350));
        ModeLibre->setFont(font1);
        ModeLibre->setStyleSheet(QString::fromUtf8("#ModeLibre {\n"
"	background : url(:/img/Img/libreicon.png) center cente no-repeat;\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 107));\n"
"	border: 1px solid rgb(255, 255, 255);\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : rgb(255, 255, 255);\n"
"}\n"
"\n"
"#ModeLibre:hover {\n"
"    background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.606178 			rgba(255, 255, 255, 150));\n"
"}\n"
"\n"
"#ModeLibre:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        horizontalLayout_15->addWidget(ModeLibre);


        gridLayout_14->addLayout(horizontalLayout_15, 2, 0, 1, 1);

        stackedWidget->addWidget(choixplateau);
        plateauofficiel = new QWidget();
        plateauofficiel->setObjectName("plateauofficiel");
        verticalLayoutWidget_8 = new QWidget(plateauofficiel);
        verticalLayoutWidget_8->setObjectName("verticalLayoutWidget_8");
        verticalLayoutWidget_8->setGeometry(QRect(10, 10, 1505, 706));
        gridLayout_10 = new QGridLayout(verticalLayoutWidget_8);
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setContentsMargins(100, 0, 100, 100);
        JouerOfficiel = new QPushButton(verticalLayoutWidget_8);
        JouerOfficiel->setObjectName("JouerOfficiel");
        JouerOfficiel->setMinimumSize(QSize(200, 40));
        JouerOfficiel->setMaximumSize(QSize(200, 40));
        JouerOfficiel->setFont(font6);
        JouerOfficiel->setStyleSheet(QString::fromUtf8("QPushButton#JouerOfficiel {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#JouerOfficiel:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#JouerOfficiel:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));

        gridLayout_10->addWidget(JouerOfficiel, 2, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(100);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, -1, 200, -1);
        graphicsView_6 = new QGraphicsView(verticalLayoutWidget_8);
        graphicsView_6->setObjectName("graphicsView_6");
        graphicsView_6->setMinimumSize(QSize(1004, 425));
        graphicsView_6->setMaximumSize(QSize(1004, 425));
        graphicsView_6->setStyleSheet(QString::fromUtf8("background : url(:/img/Img/Fond2.png) center center no-repeat;\n"
"border:none;"));

        horizontalLayout_8->addWidget(graphicsView_6);


        gridLayout_10->addLayout(horizontalLayout_8, 1, 0, 1, 1);

        stackedWidget->addWidget(plateauofficiel);
        pagecharger = new QWidget();
        pagecharger->setObjectName("pagecharger");
        verticalLayoutWidget_10 = new QWidget(pagecharger);
        verticalLayoutWidget_10->setObjectName("verticalLayoutWidget_10");
        verticalLayoutWidget_10->setGeometry(QRect(10, 10, 1261, 601));
        gridLayout_12 = new QGridLayout(verticalLayoutWidget_10);
        gridLayout_12->setObjectName("gridLayout_12");
        gridLayout_12->setContentsMargins(100, 0, 100, 100);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(100);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(100, -1, 100, -1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame_5 = new QFrame(verticalLayoutWidget_10);
        frame_5->setObjectName("frame_5");
        frame_5->setStyleSheet(QString::fromUtf8("border:none;"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        BtnCharger = new QPushButton(frame_5);
        BtnCharger->setObjectName("BtnCharger");
        BtnCharger->setGeometry(QRect(330, 300, 200, 41));
        BtnCharger->setMinimumSize(QSize(200, 0));
        BtnCharger->setMaximumSize(QSize(200, 100));
        BtnCharger->setFont(font2);
        BtnCharger->setStyleSheet(QString::fromUtf8("QPushButton#BtnCharger {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#BtnCharger:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#BtnCharger:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        listWidget_2 = new QListWidget(frame_5);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(300, 60, 256, 192));

        verticalLayout_2->addWidget(frame_5);


        horizontalLayout_6->addLayout(verticalLayout_2);


        gridLayout_12->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        stackedWidget->addWidget(pagecharger);
        utilisation = new QWidget();
        utilisation->setObjectName("utilisation");
        stackedWidget->addWidget(utilisation);
        frame_19 = new QFrame(frame);
        frame_19->setObjectName("frame_19");
        frame_19->setGeometry(QRect(10, 10, 1311, 631));
        frame_19->setStyleSheet(QString::fromUtf8("background:none;\n"
"background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:1 rgba(0, 0, 0, 0));"));
        frame_19->setFrameShape(QFrame::StyledPanel);
        frame_19->setFrameShadow(QFrame::Raised);
        frame_19->raise();
        stackedWidget->raise();
        Home = new QPushButton(centralwidget);
        Home->setObjectName("Home");
        Home->setGeometry(QRect(110, 10, 100, 100));
        Home->setMinimumSize(QSize(100, 100));
        Home->setMaximumSize(QSize(70, 70));
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font8.setBold(true);
        Home->setFont(font8);
        Home->setStyleSheet(QString::fromUtf8("QPushButton#Home{\n"
"    background : url(:/img/Img/logoRRS.png) center center no-repeat;\n"
"	border:none;\n"
"	border-radius: 50px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#Home:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#Home:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ModeJouer->setText(QCoreApplication::translate("MainWindow", "Jouer", nullptr));
        ModeEdition->setText(QCoreApplication::translate("MainWindow", "Edition", nullptr));
        ModeParametre->setText(QCoreApplication::translate("MainWindow", "Param\303\250tres", nullptr));
        AddRbt->setText(QCoreApplication::translate("MainWindow", "Robots", nullptr));
        AddObj->setText(QCoreApplication::translate("MainWindow", "Objectives", nullptr));
        Jouer->setText(QCoreApplication::translate("MainWindow", "Jouer", nullptr));
        resetPlateau->setText(QString());
        Histoire1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        Histoire2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        label_4->setText(QString());
        Histoire3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        Histoire4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        Histoire5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        Histoire6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        Histoire7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        Histoire8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        groupBox_2->setTitle(QString());
        radioButton->setText(QCoreApplication::translate("MainWindow", "4 Robots", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Robot noir", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Mur biais", nullptr));
        GenererAleatoire->setText(QCoreApplication::translate("MainWindow", "Generer", nullptr));
        label_6->setText(QString());
        ModeHistoire->setText(QCoreApplication::translate("MainWindow", "Histoire", nullptr));
        ModeEntrainement->setText(QCoreApplication::translate("MainWindow", "Entrainement", nullptr));
        ModeCharger->setText(QCoreApplication::translate("MainWindow", "Charger", nullptr));
        ModeCreer->setText(QCoreApplication::translate("MainWindow", "Creer", nullptr));
        Rejouer->setText(QCoreApplication::translate("MainWindow", "Rejouer", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        Solution->setText(QCoreApplication::translate("MainWindow", "Solution", nullptr));
        Sauvegarder->setText(QCoreApplication::translate("MainWindow", "Sauvegarder", nullptr));
        ModeOfficiel->setText(QCoreApplication::translate("MainWindow", "Officiel", nullptr));
        ModeLibre->setText(QCoreApplication::translate("MainWindow", "Libre", nullptr));
        JouerOfficiel->setText(QCoreApplication::translate("MainWindow", "Jouer", nullptr));
        BtnCharger->setText(QCoreApplication::translate("MainWindow", "Charger", nullptr));
        Home->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
