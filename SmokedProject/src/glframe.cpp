#include "glframe.h"

using namespace std;


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;

const GLfloat g_AngleSpeed = 10.0f;

Basis* g_Basis;


GlFrame::GlFrame(QWidget *parent):GlWindow(parent)
{
    setMinimumSize(1600,900);
    //resize(1024, 768);
    ps = new ParticleSystem();
    ps -> start();

    g_Basis = new Basis( 10.0 );
}


GlFrame::~GlFrame()
{
    delete g_Basis;
    delete ps;
}


bool
GlFrame::initializeObjects()
{
    // Fond gris
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_PROGRAM_POINT_SIZE );

    // Chargement des shaders
    createShader( "Shaders/color" );

    createShader( "Shaders/PerVertex" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

    return true;
}


void
GlFrame::render()
{
    // Initialisation de la caméra
    lookAt( 0, 5, 30, 0, 0, 0 );


    // Rendu des objets
    pushMatrix();
        rotate( angle1, 0, 1, 0 );
        rotate( angle2, 1, 0, 0 );
        rotate( angle2, 0, 0, 1 );

        useShader("color");
        g_Basis->draw();

        useShader("PerVertex");

        ps->lockMutex();
        if(ps->isStarted()){
            ps->updateTime();
            ps->draw();
        }
        ps->unlockMutex();
    popMatrix();

}


void
GlFrame::mouseMoveEvent(QMouseEvent *event){
    cout << "YEY SOURIS : " << event->globalX() << " " << event->globalY() << endl;
}

void
GlFrame::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
            case Qt::Key_Left:
                angle1 -= g_AngleSpeed;
                break;

            case Qt::Key_Right:
                angle1 += g_AngleSpeed;
                break;

            case Qt::Key_Up:
                angle2 -= g_AngleSpeed;
                break;

            case Qt::Key_Down:
                angle2 += g_AngleSpeed;
                break;

            case Qt::Key_R:
                angle1 = angle2 = 0.0f;
                break;

            case Qt::Key_S:
                ps->stop();
    }
}

QSize GlFrame::minimumSizeHint() const
{
    return QSize(300,300);
}

QSize GlFrame::sizeHint() const
{
    return QSize(1024,600);
}


ParticleSystem * GlFrame::getParticleSytem()
{
    return ps;
}
