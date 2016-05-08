#include "mainwindow.h"
#include <QApplication>
#include "GlFrame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    GlFrame win;
    win.show();

    return a.exec();
}
