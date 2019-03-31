#include "board.h"
#include "mainwindow.h"
#include "webcam.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Board w;
    MainWindow w;
    w.show();

    return a.exec();
}
