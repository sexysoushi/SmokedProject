#include "glframe.h"

/////////// PUBLIC /////////////

/***** LIFE CYCLE *****/

GlFrame::GlFrame(QWidget *parent):GlWindow(parent)
{
    ParticleSystem* ps = new ParticleSystem();
    m_systems.push_back(ps);
    ps -> start();

    m_currentTime = Clock::now();

    m_Basis = new Basis( 10.0 );
    m_Camera = new Camera(0.0f, 5.0f, 30.0f, 16.0f/9.0f, 0.3f, 1000.0f, 60.0f);
    m_Skybox = new Skybox();

    m_rotateSpeed = 0.001;
    m_moveSpeed = 1.0f / 30.0f;

    setMouseTracking(true);
}


GlFrame::~GlFrame()
{
    delete m_Basis;
    delete m_Camera;
    delete m_Skybox;
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
    m_Skybox->loadGLTextures();

    return true;
}

////
/// \brief GlFrame::render
/// Rendering function to be called at each frame
///
void GlFrame::render()
{
    m_timeSinceLastFrame = timeInterval(m_currentTime, Clock::now());
    m_currentTime = Clock::now();

    applyCameraTransformations();

    // Rendu des objets
    pushMatrix();
        //useShader("color");
        //g_Basis->draw();

        for(unsigned int i=0; i<m_systems.size(); i++){
            pushMatrix();
            //translate(i, 0, 0);
            m_systems[i]->draw();
            popMatrix();
        }

    popMatrix();
}

/****** OPERATIONS *****/

///
/// \brief GlFrame::addParticleSystem
///      Adds a previously instanciated particle system to the list of systems to be rendered
///
/// \param ps An allocated particle system pointer
///
void GlFrame::addParticleSystem(ParticleSystem *ps)
{
    if(ps != NULL)
        m_systems.push_back(ps);
    else
        std::cout << "ALERTE AU GOGOLE !";
}

///
/// \brief GlFrame::clear
///     Clears the list of particle systems
///
void GlFrame::clear()
{
    m_systems.clear();
}

///
/// \brief GlFrame::applyCameraTransformations
///     Apply camera transforms from current orientation
///     This is called at every frame in the rendering loop
///
void GlFrame::applyCameraTransformations()
{
    pProjMatrix = m_Camera->getProjectionMatrix();
    pViewMatrix = m_Camera->getViewMatrix();

    Vec3 pos = m_Camera->getPosition();
    Quaternion rot = m_Camera->getOrientation();

    Quaternion q_lookat = rot * Quaternion(0.0f, 0.0f, 0.0f, -1.0f) * rot.conjugate();
    q_lookat.normalize();

    Quaternion q_up = rot * Quaternion(0.0f, 0.0f, 1.0f, 0.0f) * rot.conjugate();
    q_up.normalize();

//    std::cout << "POS : " << pos.x << " ; " << pos.y << " ; " << pos.z << std::endl;
//    std::cout << "LOOK : " << q_lookat.x << " ; " << q_lookat.y << " ; " << q_lookat.z << std::endl;

    lookAt(pos.x, pos.y, pos.z, pos.x + q_lookat.x, pos.y + q_lookat.y, pos.z + q_lookat.z, q_up.x, q_up.y, q_up.z);
}

///
/// \brief GlFrame::rotateCamera
///     Rotates the camera around X and Y axis
/// \param angleY radians
/// \param angleX radians
///
void GlFrame::rotateCamera(float angleY, float angleX)
{
    m_Camera -> rotateY(angleY);

    Quaternion rot = m_Camera->getOrientation();
    Quaternion q_side = rot * Quaternion(0.0f, 1.0f, 0.0f, 0.0f) * rot.conjugate();
    m_Camera -> rotate(angleX, q_side.x, q_side.y, q_side.z);
}


///
/// \brief GlFrame::translateCamera
///     Translates camera along X and Z axis
/// \param forward gl units
/// \param right gl units
///
void GlFrame::translateCamera(float forward, float right)
{
    Quaternion rot = m_Camera->getOrientation();

    Quaternion q_forward = rot * Quaternion(0.0f, 0.0f, 0.0f, -1.0f) * rot.conjugate();
    q_forward.normalize();

    Quaternion q_right = rot * Quaternion(0.0f, 1.0f, 0.0f, 0.0f) * rot.conjugate();
    q_right.normalize();

    float x = forward * q_forward.x + right * q_right.x;
    float y = forward * q_forward.y + right * q_right.y;
    float z = forward * q_forward.z + right * q_right.z;

    m_Camera->translate(x, y, z);
}


///////////// PROTECTED /////////////

/***** EVENT HANDLERS *****/

///
/// \brief GlFrame::mouseMoveEvent
///     Rotate camera with mouse when in fullscreen mode
/// \param event
///
void GlFrame::mouseMoveEvent(QMouseEvent *event)
{    if(!isFullScreen())
        return;

    float disX = (event->globalX() - m_lastPos.x()) * m_rotateSpeed;
    float disY = (event->globalY() - m_lastPos.y()) * m_rotateSpeed;

//    cout << "Souris y " << disY << endl;
//    cout << "Souris x " << disX << endl;

    rotateCamera(-disX, -disY);

    QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
    QCursor::setPos(glob);
    m_lastPos = QPoint(width()/2,height()/2);
}

///
/// \brief GlFrame::mouseDoubleClickEvent
///     Toggle fullscreen with double click
///
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

///
/// \brief GlFrame::wheelEvent
///     Translates along Z axis with mouse wheel
/// \param event
///
void GlFrame::wheelEvent( QWheelEvent* event )
{
    if(event->delta() > 0)
        translateCamera(-m_moveSpeed * m_timeSinceLastFrame, 0);
    else
       translateCamera(m_moveSpeed * m_timeSinceLastFrame, 0);
}

///
/// \brief GlFrame::keyPressEvent
///     Key Event handler, for translation and rotation
///         ZS : move along Z
///         QD : move along X
///         RF : move along Y
///
///         Arrow keys : rotate camera
///
/// \param event
///
void GlFrame::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
            case Qt::Key_Left:
                rotateCamera( m_rotateSpeed * m_timeSinceLastFrame, 0 );
                break;

            case Qt::Key_Right:
                rotateCamera( -m_rotateSpeed * m_timeSinceLastFrame, 0);
                break;

            case Qt::Key_Up:
                rotateCamera( 0, m_rotateSpeed * m_timeSinceLastFrame );
                break;

            case Qt::Key_Down:
                rotateCamera( 0, -m_rotateSpeed * m_timeSinceLastFrame);
                break;  

            case Qt::Key_D:
                translateCamera(0, m_moveSpeed * m_timeSinceLastFrame);
                break;

            case Qt::Key_Q:
                translateCamera(0, -m_moveSpeed * m_timeSinceLastFrame);
                break;

            case Qt::Key_Z:
                translateCamera(m_moveSpeed * m_timeSinceLastFrame, 0);
                break;

            case Qt::Key_S:
                translateCamera(-m_moveSpeed * m_timeSinceLastFrame, 0);
                break;

            case Qt::Key_R:
                m_Camera->translateY(m_moveSpeed * m_timeSinceLastFrame);
                break;

            case Qt::Key_F:
                m_Camera->translateY(-m_moveSpeed * m_timeSinceLastFrame);
                break;
    }
}

/***** Size Hints *****/

QSize GlFrame::minimumSizeHint() const
{
    return QSize(300,170);
}


QSize GlFrame::sizeHint() const
{
    return QSize(1024,600);
}

