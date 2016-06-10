#include "mainwindow.h"

//////////////// PUBLIC //////////////

///
/// \brief MainWindow::MainWindow
///     Window creation and initialization
/// \param parent
///
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{   
    // Init widgets

    rateSlide = new QSlider(Qt::Horizontal);
    rateSlide->setRange(1,10000);
    rateSlide->setSingleStep(10);
    rateSlide->setValue(400);

    nbMaxSlide = new QSlider(Qt::Horizontal);
    nbMaxSlide->setRange(1,100000);
    nbMaxSlide->setSingleStep(1000);
    nbMaxSlide->setValue(50000);

    maxTimeSlide = new QSlider(Qt::Horizontal);
    maxTimeSlide->setRange(0, 10000);
    maxTimeSlide->setSingleStep(100);
    maxTimeSlide->setValue(5000);

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

    sizeSlide = new QSlider(Qt::Horizontal);
    sizeSlide->setRange(0, 50);
    sizeSlide->setSingleStep(1);
    sizeSlide->setValue(1);


    // connect buttons signals

    addButton = new QPushButton("Add System");
    connect(addButton, SIGNAL(clicked()), this, SLOT(addParticleSystem()));

    clearButton = new QPushButton("Clear");
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));

    waterButton = new QPushButton("Water");
    connect(waterButton, SIGNAL(clicked()), this, SLOT(addWaterSystem()));

    lavaButton = new QPushButton("Lava");
    connect(lavaButton, SIGNAL(clicked()), this, SLOT(addLavaSystem()));

    smokeButton = new QPushButton("Smoke");
    connect(smokeButton, SIGNAL(clicked()), this, SLOT(addSmokeSystem()));

    fireworkButton = new QPushButton("Firework");
    connect(fireworkButton, SIGNAL(clicked()), this, SLOT(addFireworkSystem()));

    atomButton = new QPushButton("Atom");
    connect(atomButton, SIGNAL(clicked()), this, SLOT(addAtomSystem()));

    tornadoButton = new QPushButton("Tornado");
    connect(tornadoButton, SIGNAL(clicked()), this, SLOT(addTornadoSystem()));


    // create layout

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

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    topLayout->addWidget(line);

    addLabel(topLayout, "Premade effects : ");

    topLayout->addWidget(waterButton);
    topLayout->addWidget(lavaButton);
    topLayout->addWidget(smokeButton);
    topLayout->addWidget(fireworkButton);
    topLayout->addWidget(atomButton);
    topLayout->addWidget(tornadoButton);

    QWidget* topWidget = new QWidget();
    topWidget->setLayout(topLayout);
    setCentralWidget(topWidget);


    // when window is fully init, create GL window

    connect(this, SIGNAL(initDone(void)), this, SLOT(initGL(void)));
    emit initDone();
}

MainWindow::~MainWindow()
{
}


/***** Event handler *****/

void MainWindow::keyPressEvent(QKeyEvent * event){
    switch(event->key()){
    case Qt::Key_Escape:
        gl->close();
        close();
        break;
    }
}


///////////// PRIVATE /////////////

///
/// \brief MainWindow::addLabel
///     Adds label in the selected layout
/// \param l the layout
/// \param t1 the label text
///
void MainWindow::addLabel(QLayout* l, char* t1){
    QLabel* lb1 = new QLabel(t1);
    lb1->setAlignment(Qt::AlignLeft);
    l->addWidget(lb1);
}


///////////// PRIVATE SLOTS /////////////

///
/// \brief MainWindow::initGL
///     Create GL window
///
void MainWindow::initGL(){
    gl = new GlFrame();
    gl->show();
}

///
/// \brief MainWindow::clear
///     Clear scene
///
void MainWindow::clear()
{
    gl->clear();
}


/****** PARTICLE SYSTEMS ADDS ******/

///
/// \brief MainWindow::addParticleSystem
///     Create Particle System according to user inpts and add to the scene
///
void MainWindow::addParticleSystem()
{
    ParticleSystem* s = new ParticleSystem(
        rateSlide->value(),
        nbMaxSlide->value(),
        maxTimeSlide->value(),
        spreadSlide->value(),
        speedSlide->value(),
        gravitySlide->value(),
        vec3{0,-1,0},
        sizeSlide->value()
    );

    s->setTransparent(false);

    gl->addParticleSystem(s);
    s->start();
}


/***** PREMADE PARTICLE EFFECTS *****/

void MainWindow::addWaterSystem()
{
    gl->clear();
    ParticleSystem* s = new ParticleSystem(1000,50000,8000,40,8,2,vec3{0,-1,0},1.5);

    s->setShader("Liquid");
    s->loadTexture("water.png");

    gl->addParticleSystem(s);
    s->start();
}

void MainWindow::addLavaSystem()
{
    gl->clear();
    ParticleSystem* s = new ParticleSystem(100,500,5000,20,4,1,vec3{0,-1,0},20);

    s->setShader("Liquid");
    s->loadTexture("lava.jpg");

    gl->addParticleSystem(s);
    s->start();
}

void MainWindow::addSmokeSystem()
{
    gl->clear();
    ParticleSystem* s = new ParticleSystem(100,500,5000,90,2,0,vec3{0,-1,0},15);

    s->setShader("Smoke");
    s->loadTexture("smoke.png");

    gl->addParticleSystem(s);
    s->start();
}


void MainWindow::addFireworkSystem()
{
    gl->clear();
    ParticleSystem* s = new ParticleSystem(400,2000,1000,90,2,0.2,vec3{0,-1,0},2);

    s->setShader("Firework");

    gl->addParticleSystem(s);
    s->start();
}

void MainWindow::addAtomSystem()
{
    gl->clear();
    ParticleSystem* s = new ParticleSystem(200,5000,0,90,2,0,vec3{0,-1,0},4);

    s->setShader("Atome");
    s->loadTexture("electron.jpg");

    gl->addParticleSystem(s);
    s->start();
}


void MainWindow::addTornadoSystem()
{
    gl->clear();
    ParticleSystem* s = new ParticleSystem(100,2000,4000,40,2,0.2,vec3{0,-1,0},7);

    s->setShader("Tornade");
    s->loadTexture("smoke.png");

    gl->addParticleSystem(s);
    s->start();
}
