#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{   
    rateSlide = new QSlider(Qt::Horizontal);
    rateSlide->setRange(1,10000);
    rateSlide->setSingleStep(10);
    rateSlide->setValue(1000);

    nbMaxSlide = new QSlider(Qt::Horizontal);
    nbMaxSlide->setRange(1,100000);
    nbMaxSlide->setSingleStep(1000);
    nbMaxSlide->setValue(50000);

    maxTimeSlide = new QSlider(Qt::Horizontal);
    maxTimeSlide->setRange(0, 10000);
    maxTimeSlide->setSingleStep(100);
    maxTimeSlide->setValue(3000);

    speedSlide = new QSlider(Qt::Horizontal);
    speedSlide->setRange(0.5, 25);
    speedSlide->setSingleStep(0.5);
    speedSlide->setValue(8);

    gravitySlide = new QSlider(Qt::Horizontal);
    gravitySlide->setRange(0,25);
    gravitySlide->setSingleStep(0.5);
    gravitySlide->setValue(2);

    spreadSlide = new QSlider(Qt::Horizontal);
    spreadSlide->setRange(0, 180);
    spreadSlide->setSingleStep(1);
    spreadSlide->setValue(45);

    addButton = new QPushButton("Add System");
    connect(addButton, SIGNAL(clicked()), this, SLOT(addParticleSystem()));

    clearButton = new QPushButton("Clear");
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));

    QVBoxLayout* topLayout = new QVBoxLayout();

    addLabel(topLayout, "rate:");
    topLayout->addWidget(rateSlide);

    addLabel(topLayout, "nb max:");
    topLayout->addWidget(nbMaxSlide);

    addLabel(topLayout, "max time:");
    topLayout->addWidget(maxTimeSlide);

    addLabel(topLayout, "speed:");
    topLayout->addWidget(speedSlide);

    addLabel(topLayout, "gravity:");
    topLayout->addWidget(gravitySlide);

    addLabel(topLayout, "spread:");
    topLayout->addWidget(spreadSlide);

    topLayout->addWidget(addButton);

    topLayout->addWidget(clearButton);

    QWidget* topWidget = new QWidget();
    topWidget->setLayout(topLayout);
    setCentralWidget(topWidget);


    connect(this, SIGNAL(initDone(void)), this, SLOT(initGL(void)));
    emit initDone();
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent * event){
    switch(event->key()){
    case Qt::Key_Escape:
        gl->close();
        close();
        break;
    }
}

void MainWindow::initGL(){
    gl = new GlFrame();
    gl->show();
}

void MainWindow::addParticleSystem()
{
    ParticleSystem* s = new ParticleSystem(
        rateSlide->value(),
        nbMaxSlide->value(),
        maxTimeSlide->value(),
        spreadSlide->value(),
        speedSlide->value(),
        gravitySlide->value(),
        vec3{0,-1,0}
    );

    gl->addParticleSystem(s);
    s->start();
}

void MainWindow::clear()
{
    gl->clear();
}

void MainWindow::addLabel(QLayout* l, char* t1){
    QLabel* lb1 = new QLabel(t1);
    lb1->setAlignment(Qt::AlignLeft);
    l->addWidget(lb1);
}
