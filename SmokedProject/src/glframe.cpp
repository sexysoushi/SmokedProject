#include "glframe.h"

GlFrame::GlFrame(QWidget *parent):GlWindow(parent)
{
    ParticleSystem* ps = new ParticleSystem();
    p_systems.push_back(ps);
    ps -> start();

    g_Basis = new Basis( 10.0 );
    g_Camera = new Camera(0.0f, 5.0f, 30.0f, 4.0f/3.0f, 0.3f, 1000.0f, 60.0f);
}


GlFrame::~GlFrame()
{
    delete g_Basis;
    delete g_Camera;
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
    createShader( "Shaders/Tornade" );
    createShader( "Shaders/Firework" );
    createShader( "Shaders/Atome" );
    createShader( "Shaders/DamierTexture" );

    // Chargement des textures
    const int NBR_TEXTURES = 2;
    GLuint texId[NBR_TEXTURES];
    glGenTextures( NBR_TEXTURES, texId );
    // Initialisation de la première texture stockée dans l'unité de texture #0
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texId[0] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture1_width, texture1_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tab_texture1 );
    // Initialisation de la seconde texture stockée dans l'unité de texture #1
    glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_2D, texId[1] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture2_width, texture2_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tab_texture2 );

    return true;
}


void
GlFrame::render()
{
    // Initialisation de la caméra
    pProjMatrix = g_Camera->getProjectionMatrix();
    pViewMatrix = g_Camera->getViewMatrix();

    // Rendu des objets
    pushMatrix();
        rotate( angle1, 0, 1, 0 );
        rotate( angle2, 1, 0, 0 );
        rotate( angle2, 0, 0, 1 );

        useShader("color");
        g_Basis->draw();

        //std::cout << p_systems.size() << std::endl;

        useShader("PerVertex");
        for(unsigned int i=0; i<p_systems.size(); i++){
            pushMatrix();
            //translate(i, 0, 0);
            p_systems[i]->draw();
            popMatrix();
        }

    popMatrix();

}


void
GlFrame::mouseMoveEvent(QMouseEvent *event){
    cout << "Souris X " << event->globalX();
    cout << "  Souris Y " << event->globalY() << "\n";
    //g_Camera->rotateX((float)event->globalX());
    //g_Camera->rotateY((float)event->globalY());
}

void
GlFrame::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
            case Qt::Key_Left:
                g_Camera->translateX(1.0f);
                break;

            case Qt::Key_Right:
                g_Camera->translateX(-1.0f);
                break;

            case Qt::Key_Up:
                g_Camera->translateY(-1.0f);
                break;

            case Qt::Key_Down:
                g_Camera->translateY(1.0f);
                break;
    }
}

void GlFrame::addParticleSystem(ParticleSystem *ps)
{
    if(ps != NULL)
        p_systems.push_back(ps);
    else
        std::cout << "wat";
}

void GlFrame::clear()
{
    p_systems.clear();
}

QSize GlFrame::minimumSizeHint() const
{
    return QSize(300,300);
}

QSize GlFrame::sizeHint() const
{
    return QSize(1024,600);
}
