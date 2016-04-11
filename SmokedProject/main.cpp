#include "mainwindow.h"
#include <QApplication>
#include "TP01.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TP01 win;
    win.show();

    return a.exec();
}
