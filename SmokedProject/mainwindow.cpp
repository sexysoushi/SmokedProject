#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    gl = new GlFrame(this);

    parameters = new ParametersWidget(this);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(gl);
    layout->addWidget(parameters);

    QWidget* window = new QWidget();
    window->setLayout(layout);

    setCentralWidget(window);
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
