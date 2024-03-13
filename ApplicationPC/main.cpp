#include "mainwindow.h"
#include "board.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/Img/logoRRS.png"));
    //QFontDatabase::addApplicationFont(":/img/Img/Poppins-Regular.ttf");
    QFontDatabase::addApplicationFont(":/img/Img/RubikGlitchPop-Regular.ttf");
    QFontDatabase::addApplicationFont(":/img/Img/Poppins-Bold.ttf");

    Board* bd = new Board;
    MainWindow w(nullptr, bd);
    w.setWindowTitle("Ricochet Robot Solver");
    w.show();
    return a.exec();
}
