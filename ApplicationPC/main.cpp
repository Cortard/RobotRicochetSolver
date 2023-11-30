#include "mainwindow.h"
#include "board.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Board* bd = new Board;
    MainWindow w(nullptr, bd);
    w.show();
    return a.exec();
}
