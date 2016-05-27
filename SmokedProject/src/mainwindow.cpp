#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    gl = new GlFrame(this);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(gl);
    //layout->addWidget(parameters);

    QWidget* window = new QWidget();

    QWidget* w = new QWidget();
    parameters = new ParametersWidget(this);

    QHBoxLayout* pLay = new QHBoxLayout();
    pLay->addWidget(parameters);

    window->setLayout(layout);
    setCentralWidget(window);

    w->setLayout(pLay);
    w->show();

}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent * event){
    gl->keyPressEvent(event);

    switch(event->key()){
    case Qt::Key_Escape:
        close();
        break;
    }
}
