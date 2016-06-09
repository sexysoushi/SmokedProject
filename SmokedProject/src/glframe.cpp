#include "glframe.h"

GlFrame::GlFrame(QWidget *parent):GlWindow(parent)
{
    ParticleSystem* ps = new ParticleSystem();
    p_systems.push_back(ps);
    ps -> start();

    currentTime = Clock::now();

    g_Basis = new Basis( 10.0 );
    g_Camera = new Camera(0.0f, 5.0f, 30.0f, 16.0f/9.0f, 0.3f, 1000.0f, 60.0f);
    g_Skybox = new Skybox();

    rotateSpeed = 0.001;
    moveSpeed = 1.0f / 30.0f;

    setMouseTracking(true);
}


GlFrame::~GlFrame()
{
    delete g_Basis;
    delete g_Camera;
    delete g_Skybox;
}


bool GlFrame::initializeObjects()
{
    // Fond gris
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_PROGRAM_POINT_SIZE );

    // Chargement des shaders
    createShader( "Shaders/Basic" );
    createShader( "Shaders/Smoke" );
    createShader( "Shaders/Liquid" );
    createShader( "Shaders/Tornade" );
    createShader( "Shaders/Firework" );
    createShader( "Shaders/Atome" );
    //createShader( "Shaders/Skybox" );

    //charge skybox
    g_Skybox->loadGLTextures();

    return true;
}


void GlFrame::render()
{
    timeSinceLastFrame = timeInterval(currentTime, Clock::now());
    currentTime = Clock::now();

    lookat();

    // Rendu des objets
    pushMatrix();
        //useShader("color");
        //g_Basis->draw();

        //useShader("PerVertex");
        for(unsigned int i=0; i<p_systems.size(); i++){
            pushMatrix();
            //translate(i, 0, 0);
            p_systems[i]->draw();
            popMatrix();
        }

    popMatrix();

    //clos textures
    //qit->closeGLTextures();

}


void GlFrame::lookat()
{
    pProjMatrix = g_Camera->getProjectionMatrix();
    pViewMatrix = g_Camera->getViewMatrix();

    Vec3 pos = g_Camera->getPosition();
    Quaternion rot = g_Camera->getOrientation();

    Quaternion q_lookat = rot * Quaternion(0.0f, 0.0f, 0.0f, -1.0f) * rot.conjugate();
    q_lookat.normalize();

    Quaternion q_up = rot * Quaternion(0.0f, 0.0f, 1.0f, 0.0f) * rot.conjugate();
    q_up.normalize();

//    std::cout << "POS : " << pos.x << " ; " << pos.y << " ; " << pos.z << std::endl;
//    std::cout << "LOOK : " << q_lookat.x << " ; " << q_lookat.y << " ; " << q_lookat.z << std::endl;

    lookAt(pos.x, pos.y, pos.z, pos.x + q_lookat.x, pos.y + q_lookat.y, pos.z + q_lookat.z, q_up.x, q_up.y, q_up.z);
}



void GlFrame::rotateCamera(float angleY, float angleX)
{
    g_Camera -> rotateY(angleY);

    Quaternion rot = g_Camera->getOrientation();
    Quaternion q_side = rot * Quaternion(0.0f, 1.0f, 0.0f, 0.0f) * rot.conjugate();
    g_Camera -> rotate(angleX, q_side.x, q_side.y, q_side.z);
}



void GlFrame::translateCamera(float forward, float right)
{
    Quaternion rot = g_Camera->getOrientation();

    Quaternion q_forward = rot * Quaternion(0.0f, 0.0f, 0.0f, -1.0f) * rot.conjugate();
    q_forward.normalize();

    Quaternion q_right = rot * Quaternion(0.0f, 1.0f, 0.0f, 0.0f) * rot.conjugate();
    q_right.normalize();

    float x = forward * q_forward.x + right * q_right.x;
    float y = forward * q_forward.y + right * q_right.y;
    float z = forward * q_forward.z + right * q_right.z;

    g_Camera->translate(x, y, z);
}



void GlFrame::mouseMoveEvent(QMouseEvent *event)
{    if(!isFullScreen())
        return;

    float disX = (event->globalX() - lastPos.x()) * rotateSpeed;
    float disY = (event->globalY() - lastPos.y()) * rotateSpeed;

//    cout << "Souris y " << disY << endl;
//    cout << "Souris x " << disX << endl;

    rotateCamera(-disX, -disY);

    QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
    QCursor::setPos(glob);
    lastPos = QPoint(width()/2,height()/2);
}



void GlFrame::mousePressEvent(QMouseEvent *event)
{
    if(isFullScreen())
        return;

    lastPos.setX(event->globalX());
    lastPos.setY(event->globalY());
}



void GlFrame::mouseDoubleClickEvent(QMouseEvent *)
{
    if(isFullScreen())
    {
        this->setWindowState(Qt::WindowNoState);
        setCursor(Qt::ArrowCursor);

    }
    else
    {
        this->setWindowState(Qt::WindowFullScreen);
        setCursor(Qt::BlankCursor);
    }
}

void
GlFrame::wheelEvent( QWheelEvent* event )
{
    if(event->delta() > 0)
        translateCamera(-moveSpeed * timeSinceLastFrame, 0);
    else
       translateCamera(moveSpeed * timeSinceLastFrame, 0);
}

void GlFrame::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
            case Qt::Key_Left:
                rotateCamera( rotateSpeed * timeSinceLastFrame, 0 );
                break;

            case Qt::Key_Right:
                rotateCamera( -rotateSpeed * timeSinceLastFrame, 0);
                break;

            case Qt::Key_Up:
                rotateCamera( 0, rotateSpeed * timeSinceLastFrame );
                break;

            case Qt::Key_Down:
                rotateCamera( 0, -rotateSpeed * timeSinceLastFrame);
                break;  

            case Qt::Key_D:
                translateCamera(0, moveSpeed * timeSinceLastFrame);
                break;

            case Qt::Key_Q:
                translateCamera(0, -moveSpeed * timeSinceLastFrame);
                break;

            case Qt::Key_Z:
                translateCamera(moveSpeed * timeSinceLastFrame, 0);
                break;

            case Qt::Key_S:
                translateCamera(-moveSpeed * timeSinceLastFrame, 0);
                break;

            case Qt::Key_R:
                g_Camera->translateY(moveSpeed * timeSinceLastFrame);
                break;

            case Qt::Key_F:
                g_Camera->translateY(-moveSpeed * timeSinceLastFrame);
                break;
    }
}


void GlFrame::addParticleSystem(ParticleSystem *ps)
{
    if(ps != NULL)
        p_systems.push_back(ps);
    else
        std::cout << "ALERTE AU GOGOLE !";
}


void GlFrame::clear()
{
    p_systems.clear();
}


QSize GlFrame::minimumSizeHint() const
{
    return QSize(300,170);
}


QSize GlFrame::sizeHint() const
{
    return QSize(1024,600);
}

