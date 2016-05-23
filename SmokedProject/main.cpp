#include <QApplication>
//#include "GlFrame.h"

//#include "Cameratest.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    GlFrame win;
//    win.show();

    MainWindow win;
    win.show();

    return a.exec();
}
