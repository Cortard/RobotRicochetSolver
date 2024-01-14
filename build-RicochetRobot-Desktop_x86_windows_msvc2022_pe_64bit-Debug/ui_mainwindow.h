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
    QPushButton *pushButtonJouer;
    QPushButton *pushButton_21;
    QPushButton *pushButton_22;
    QWidget *pageplateau;
    QWidget *verticalLayoutWidget_4;
    QGridLayout *gridLayout_6;
    QPushButton *Home_3;
    QPushButton *Retour_4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QFrame *frame_4;
    QPushButton *pushRobot;
    QPushButton *pushObjective;
    QPushButton *pushPlateau;
    QGraphicsView *graphicsView_2;
    QWidget *pagehistoire;
    QWidget *verticalLayoutWidget_2;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QGraphicsView *graphicsView;
    QPushButton *Retour_3;
    QLabel *label_4;
    QPushButton *Home;
    QWidget *pagetrain;
    QWidget *verticalLayoutWidget_3;
    QGridLayout *gridLayout_7;
    QPushButton *Retour_5;
    QPushButton *Home_2;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_2;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QPushButton *pushButton_5;
    QWidget *widget;
    QGroupBox *groupBox;
    QListWidget *listWidget;
    QPushButton *pushButton_4;
    QWidget *pagejouer;
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushHistoire;
    QPushButton *pushTrain;
    QLabel *label_2;
    QPushButton *Retour;
    QWidget *edition;
    QWidget *verticalLayoutWidget_5;
    QGridLayout *gridLayout_4;
    QPushButton *Retour_2;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushHistoire_2;
    QPushButton *pushTrain_2;
    QWidget *plateau;
    QWidget *verticalLayoutWidget_6;
    QGridLayout *gridLayout_9;
    QPushButton *Home_5;
    QPushButton *Retour_7;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_7;
    QPushButton *pushObjective_3;
    QLabel *label;
    QGraphicsView *graphicsView_4;
    QWidget *choixplateau;
    QWidget *verticalLayoutWidget_7;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushHistoire_3;
    QPushButton *pushTrain_3;
    QLabel *label_3;
    QPushButton *Retour_6;
    QWidget *plateauofficiel;
    QWidget *verticalLayoutWidget_8;
    QGridLayout *gridLayout_10;
    QPushButton *Home_4;
    QPushButton *Retour_8;
    QHBoxLayout *horizontalLayout_8;
    QGraphicsView *graphicsView_6;
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
        frame->setStyleSheet(QString::fromUtf8("background : url(:/img/galaxy.png) center center;"));
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
        frame_3->setStyleSheet(QString::fromUtf8("background : url(:/img/nom.png) center center no-repeat;\n"
"border:none;"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);

        verticalLayout_10->addWidget(frame_3);

        frame_2 = new QFrame(gridLayoutWidget_2);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("border:none;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButtonJouer = new QPushButton(frame_2);
        pushButtonJouer->setObjectName("pushButtonJouer");
        pushButtonJouer->setGeometry(QRect(50, 50, 571, 71));
        pushButtonJouer->setMaximumSize(QSize(666666, 100));
        QFont font;
        font.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font.setPointSize(25);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        pushButtonJouer->setFont(font);
        pushButtonJouer->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonJouer->setStyleSheet(QString::fromUtf8("QPushButton#pushButtonJouer {\n"
"    background-color: #ba3f96;\n"
"	border:none;\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#pushButtonJouer:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#pushButtonJouer:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        pushButton_21 = new QPushButton(frame_2);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(50, 150, 571, 71));
        pushButton_21->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font1.setPointSize(25);
        font1.setBold(true);
        pushButton_21->setFont(font1);
        pushButton_21->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_21 {\n"
"    background-color: #ba3f96;\n"
"	border:none;\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#pushButton_21:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#pushButton_21:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        pushButton_22 = new QPushButton(frame_2);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(48, 249, 571, 71));
        pushButton_22->setMaximumSize(QSize(16777215, 100));
        pushButton_22->setFont(font1);
        pushButton_22->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_22 {\n"
"    background-color: #ba3f96;\n"
"	border:none;\n"
"	border-radius: 25px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#pushButton_22:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#pushButton_22:pressed {\n"
"    background-color: #9c2579;     \n"
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
        verticalLayoutWidget_4->setGeometry(QRect(10, 10, 1261, 601));
        gridLayout_6 = new QGridLayout(verticalLayoutWidget_4);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(100, 0, 100, 100);
        Home_3 = new QPushButton(verticalLayoutWidget_4);
        Home_3->setObjectName("Home_3");

        gridLayout_6->addWidget(Home_3, 1, 0, 1, 1, Qt::AlignLeft);

        Retour_4 = new QPushButton(verticalLayoutWidget_4);
        Retour_4->setObjectName("Retour_4");

        gridLayout_6->addWidget(Retour_4, 2, 0, 1, 1, Qt::AlignLeft);

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
        pushRobot = new QPushButton(frame_4);
        pushRobot->setObjectName("pushRobot");
        pushRobot->setGeometry(QRect(70, 110, 200, 41));
        pushRobot->setMinimumSize(QSize(200, 0));
        pushRobot->setMaximumSize(QSize(200, 100));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font2.setPointSize(15);
        pushRobot->setFont(font2);
        pushRobot->setStyleSheet(QString::fromUtf8("QPushButton#pushRobot {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#pushRobot:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#pushRobot:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        pushObjective = new QPushButton(frame_4);
        pushObjective->setObjectName("pushObjective");
        pushObjective->setGeometry(QRect(70, 200, 200, 41));
        pushObjective->setMinimumSize(QSize(200, 0));
        pushObjective->setMaximumSize(QSize(200, 100));
        pushObjective->setFont(font2);
        pushObjective->setStyleSheet(QString::fromUtf8("QPushButton#pushObjective {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#pushObjective:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#pushObjective:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        pushPlateau = new QPushButton(frame_4);
        pushPlateau->setObjectName("pushPlateau");
        pushPlateau->setGeometry(QRect(70, 290, 200, 41));
        pushPlateau->setMinimumSize(QSize(200, 0));
        pushPlateau->setMaximumSize(QSize(200, 100));
        pushPlateau->setFont(font2);
        pushPlateau->setStyleSheet(QString::fromUtf8("QPushButton#pushPlateau {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#pushPlateau:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#pushPlateau:pressed {\n"
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
        graphicsView_2->setStyleSheet(QString::fromUtf8("background : url(:/img/fond.png) center center;"));

        horizontalLayout_4->addWidget(graphicsView_2);


        gridLayout_6->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        stackedWidget->addWidget(pageplateau);
        pagehistoire = new QWidget();
        pagehistoire->setObjectName("pagehistoire");
        verticalLayoutWidget_2 = new QWidget(pagehistoire);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 1261, 701));
        gridLayout_5 = new QGridLayout(verticalLayoutWidget_2);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(100, 0, 100, 200);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(150);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(100, -1, 100, -1);
        graphicsView = new QGraphicsView(verticalLayoutWidget_2);
        graphicsView->setObjectName("graphicsView");

        horizontalLayout_3->addWidget(graphicsView);


        gridLayout_5->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        Retour_3 = new QPushButton(verticalLayoutWidget_2);
        Retour_3->setObjectName("Retour_3");

        gridLayout_5->addWidget(Retour_3, 2, 0, 1, 1, Qt::AlignLeft);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName("label_4");
        QFont font3;
        font3.setPointSize(30);
        font3.setBold(true);
        label_4->setFont(font3);
        label_4->setStyleSheet(QString::fromUtf8("color:rgb(194, 167, 225);"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_4, 3, 0, 1, 1);

        Home = new QPushButton(verticalLayoutWidget_2);
        Home->setObjectName("Home");

        gridLayout_5->addWidget(Home, 1, 0, 1, 1, Qt::AlignLeft);

        stackedWidget->addWidget(pagehistoire);
        pagetrain = new QWidget();
        pagetrain->setObjectName("pagetrain");
        verticalLayoutWidget_3 = new QWidget(pagetrain);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 1261, 701));
        gridLayout_7 = new QGridLayout(verticalLayoutWidget_3);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(100, 0, 100, 0);
        Retour_5 = new QPushButton(verticalLayoutWidget_3);
        Retour_5->setObjectName("Retour_5");

        gridLayout_7->addWidget(Retour_5, 1, 0, 1, 1, Qt::AlignLeft);

        Home_2 = new QPushButton(verticalLayoutWidget_3);
        Home_2->setObjectName("Home_2");

        gridLayout_7->addWidget(Home_2, 0, 0, 1, 1, Qt::AlignLeft);

        label_6 = new QLabel(verticalLayoutWidget_3);
        label_6->setObjectName("label_6");
        label_6->setMaximumSize(QSize(16777215, 200));
        label_6->setFont(font3);
        label_6->setStyleSheet(QString::fromUtf8("color:rgb(194, 167, 225);"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_6, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(150);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(100, -1, 100, -1);
        widget_2 = new QWidget(verticalLayoutWidget_3);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8(""));
        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(0, 0, 351, 421));
        radioButton = new QRadioButton(groupBox_2);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(10, 30, 106, 22));
        radioButton_2 = new QRadioButton(groupBox_2);
        buttonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(10, 60, 106, 22));
        radioButton_3 = new QRadioButton(groupBox_2);
        buttonGroup->addButton(radioButton_3);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(10, 90, 106, 22));
        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(140, 130, 83, 24));

        horizontalLayout_5->addWidget(widget_2);

        widget = new QWidget(verticalLayoutWidget_3);
        widget->setObjectName("widget");
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 351, 421));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 20, 351, 361));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(140, 390, 83, 24));

        horizontalLayout_5->addWidget(widget);


        gridLayout_7->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        stackedWidget->addWidget(pagetrain);
        pagejouer = new QWidget();
        pagejouer->setObjectName("pagejouer");
        pagejouer->setMinimumSize(QSize(1280, 720));
        pagejouer->setMaximumSize(QSize(1280, 720));
        verticalLayoutWidget = new QWidget(pagejouer);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 1261, 701));
        gridLayout_3 = new QGridLayout(verticalLayoutWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(100, 0, 100, 200);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(150);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(100, -1, 100, -1);
        pushHistoire = new QPushButton(verticalLayoutWidget);
        pushHistoire->setObjectName("pushHistoire");
        pushHistoire->setMinimumSize(QSize(350, 350));
        pushHistoire->setMaximumSize(QSize(350, 350));
        pushHistoire->setStyleSheet(QString::fromUtf8("background : url(:/img/histoire.jpg) center center;"));

        horizontalLayout->addWidget(pushHistoire);

        pushTrain = new QPushButton(verticalLayoutWidget);
        pushTrain->setObjectName("pushTrain");
        pushTrain->setMinimumSize(QSize(350, 350));
        pushTrain->setMaximumSize(QSize(350, 350));
        pushTrain->setStyleSheet(QString::fromUtf8("background : url(:/img/train.png) center center;"));

        horizontalLayout->addWidget(pushTrain);


        gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font3);
        label_2->setStyleSheet(QString::fromUtf8("color:rgb(194, 167, 225);"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_2, 2, 0, 1, 1);

        Retour = new QPushButton(verticalLayoutWidget);
        Retour->setObjectName("Retour");

        gridLayout_3->addWidget(Retour, 1, 0, 1, 1, Qt::AlignLeft);

        stackedWidget->addWidget(pagejouer);
        edition = new QWidget();
        edition->setObjectName("edition");
        verticalLayoutWidget_5 = new QWidget(edition);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(0, 0, 1261, 701));
        gridLayout_4 = new QGridLayout(verticalLayoutWidget_5);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(100, 0, 100, 200);
        Retour_2 = new QPushButton(verticalLayoutWidget_5);
        Retour_2->setObjectName("Retour_2");

        gridLayout_4->addWidget(Retour_2, 1, 0, 1, 1, Qt::AlignLeft);

        frame_5 = new QFrame(verticalLayoutWidget_5);
        frame_5->setObjectName("frame_5");
        frame_5->setStyleSheet(QString::fromUtf8("background : url(:/img/edition.png) center center no-repeat;\n"
"border:none;"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(frame_5, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(150);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(100, -1, 100, -1);
        pushHistoire_2 = new QPushButton(verticalLayoutWidget_5);
        pushHistoire_2->setObjectName("pushHistoire_2");
        pushHistoire_2->setMinimumSize(QSize(350, 350));
        pushHistoire_2->setMaximumSize(QSize(350, 350));
        pushHistoire_2->setStyleSheet(QString::fromUtf8("background : url(:/img/charger.png) center center;\n"
"border:none;"));

        horizontalLayout_2->addWidget(pushHistoire_2);

        pushTrain_2 = new QPushButton(verticalLayoutWidget_5);
        pushTrain_2->setObjectName("pushTrain_2");
        pushTrain_2->setMinimumSize(QSize(350, 350));
        pushTrain_2->setMaximumSize(QSize(350, 350));
        pushTrain_2->setStyleSheet(QString::fromUtf8("background : url(:/img/creer.jpg) center center;\n"
"border:none;"));

        horizontalLayout_2->addWidget(pushTrain_2);


        gridLayout_4->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        stackedWidget->addWidget(edition);
        plateau = new QWidget();
        plateau->setObjectName("plateau");
        verticalLayoutWidget_6 = new QWidget(plateau);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(10, 10, 1261, 601));
        gridLayout_9 = new QGridLayout(verticalLayoutWidget_6);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(100, 0, 100, 100);
        Home_5 = new QPushButton(verticalLayoutWidget_6);
        Home_5->setObjectName("Home_5");

        gridLayout_9->addWidget(Home_5, 1, 0, 1, 1, Qt::AlignLeft);

        Retour_7 = new QPushButton(verticalLayoutWidget_6);
        Retour_7->setObjectName("Retour_7");

        gridLayout_9->addWidget(Retour_7, 2, 0, 1, 1, Qt::AlignLeft);

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
        pushObjective_3 = new QPushButton(frame_7);
        pushObjective_3->setObjectName("pushObjective_3");
        pushObjective_3->setGeometry(QRect(80, 220, 200, 41));
        pushObjective_3->setMinimumSize(QSize(200, 0));
        pushObjective_3->setMaximumSize(QSize(200, 100));
        pushObjective_3->setFont(font2);
        pushObjective_3->setStyleSheet(QString::fromUtf8("QPushButton#pushObjective_3 {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.477, x2:1, y2:0.483, stop:0 rgba(232, 186, 255, 255), stop:1 rgba(170, 0, 255, 255));\n"
"	border:none;\n"
"	border-radius: 5px;\n"
"	padding:10px;\n"
"	color : #70bfcb;\n"
"}\n"
"\n"
"QPushButton#pushObjective_3:hover {\n"
"    background-color: #9c2579;\n"
"}\n"
"\n"
"QPushButton#pushObjective_3:pressed {\n"
"    background-color: #9c2579;     \n"
"}\n"
"\n"
""));
        label = new QLabel(frame_7);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 150, 31, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Quicksand Medium")});
        font4.setPointSize(20);
        label->setFont(font4);

        verticalLayout_3->addWidget(frame_7);


        horizontalLayout_7->addLayout(verticalLayout_3);

        graphicsView_4 = new QGraphicsView(verticalLayoutWidget_6);
        graphicsView_4->setObjectName("graphicsView_4");
        graphicsView_4->setMinimumSize(QSize(405, 405));
        graphicsView_4->setMaximumSize(QSize(405, 405));
        graphicsView_4->setStyleSheet(QString::fromUtf8("background : url(:/img/fond.png) center center;"));

        horizontalLayout_7->addWidget(graphicsView_4);


        gridLayout_9->addLayout(horizontalLayout_7, 3, 0, 1, 1);

        stackedWidget->addWidget(plateau);
        choixplateau = new QWidget();
        choixplateau->setObjectName("choixplateau");
        verticalLayoutWidget_7 = new QWidget(choixplateau);
        verticalLayoutWidget_7->setObjectName("verticalLayoutWidget_7");
        verticalLayoutWidget_7->setGeometry(QRect(10, 10, 1261, 701));
        gridLayout_8 = new QGridLayout(verticalLayoutWidget_7);
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_8->setContentsMargins(100, 0, 100, 200);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(150);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(100, -1, 100, -1);
        pushHistoire_3 = new QPushButton(verticalLayoutWidget_7);
        pushHistoire_3->setObjectName("pushHistoire_3");
        pushHistoire_3->setMinimumSize(QSize(350, 350));
        pushHistoire_3->setMaximumSize(QSize(350, 350));
        pushHistoire_3->setStyleSheet(QString::fromUtf8("background : url(:/img/histoire.jpg) center center;"));

        horizontalLayout_6->addWidget(pushHistoire_3);

        pushTrain_3 = new QPushButton(verticalLayoutWidget_7);
        pushTrain_3->setObjectName("pushTrain_3");
        pushTrain_3->setMinimumSize(QSize(350, 350));
        pushTrain_3->setMaximumSize(QSize(350, 350));
        pushTrain_3->setStyleSheet(QString::fromUtf8("background : url(:/img/train.png) center center;"));

        horizontalLayout_6->addWidget(pushTrain_3);


        gridLayout_8->addLayout(horizontalLayout_6, 3, 0, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget_7);
        label_3->setObjectName("label_3");
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("color:rgb(194, 167, 225);"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_3, 2, 0, 1, 1);

        Retour_6 = new QPushButton(verticalLayoutWidget_7);
        Retour_6->setObjectName("Retour_6");

        gridLayout_8->addWidget(Retour_6, 1, 0, 1, 1, Qt::AlignLeft);

        stackedWidget->addWidget(choixplateau);
        plateauofficiel = new QWidget();
        plateauofficiel->setObjectName("plateauofficiel");
        verticalLayoutWidget_8 = new QWidget(plateauofficiel);
        verticalLayoutWidget_8->setObjectName("verticalLayoutWidget_8");
        verticalLayoutWidget_8->setGeometry(QRect(10, 10, 1501, 601));
        gridLayout_10 = new QGridLayout(verticalLayoutWidget_8);
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setContentsMargins(100, 0, 100, 100);
        Home_4 = new QPushButton(verticalLayoutWidget_8);
        Home_4->setObjectName("Home_4");

        gridLayout_10->addWidget(Home_4, 1, 0, 1, 1, Qt::AlignLeft);

        Retour_8 = new QPushButton(verticalLayoutWidget_8);
        Retour_8->setObjectName("Retour_8");

        gridLayout_10->addWidget(Retour_8, 2, 0, 1, 1, Qt::AlignLeft);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(100);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, -1, 200, -1);
        graphicsView_6 = new QGraphicsView(verticalLayoutWidget_8);
        graphicsView_6->setObjectName("graphicsView_6");
        graphicsView_6->setMinimumSize(QSize(1004, 425));
        graphicsView_6->setMaximumSize(QSize(1004, 425));
        graphicsView_6->setStyleSheet(QString::fromUtf8("background : url(:/img/Fond2.png) center center no-repeat;"));

        horizontalLayout_8->addWidget(graphicsView_6);


        gridLayout_10->addLayout(horizontalLayout_8, 3, 0, 1, 1);

        stackedWidget->addWidget(plateauofficiel);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonJouer->setText(QCoreApplication::translate("MainWindow", "Jouer", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "Edition", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "Param\303\250tres", nullptr));
        Home_3->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        Retour_4->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        pushRobot->setText(QCoreApplication::translate("MainWindow", "Robots", nullptr));
        pushObjective->setText(QCoreApplication::translate("MainWindow", "Objectives", nullptr));
        pushPlateau->setText(QCoreApplication::translate("MainWindow", "Jouer", nullptr));
        Retour_3->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Histoire", nullptr));
        Home->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        Retour_5->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        Home_2->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Entrainement", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer Plateau", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "4 Robots", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Robot noir", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Mur biais", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Charger Plateau", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushHistoire->setText(QCoreApplication::translate("MainWindow", "Mode Histoire", nullptr));
        pushTrain->setText(QCoreApplication::translate("MainWindow", "Entrainement", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Jouer", nullptr));
        Retour->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        Retour_2->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        pushHistoire_2->setText(QCoreApplication::translate("MainWindow", "Ouvrir", nullptr));
        pushTrain_2->setText(QCoreApplication::translate("MainWindow", "Creer", nullptr));
        Home_5->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        Retour_7->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        pushObjective_3->setText(QCoreApplication::translate("MainWindow", "Solution", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushHistoire_3->setText(QCoreApplication::translate("MainWindow", "Officiel", nullptr));
        pushTrain_3->setText(QCoreApplication::translate("MainWindow", "Libre", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Edition", nullptr));
        Retour_6->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        Home_4->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        Retour_8->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
