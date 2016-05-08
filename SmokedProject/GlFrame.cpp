#include "GlFrame.h"


#include "Shapes/Basis.h"
#include "particlesystem.h"

#include <iostream>

using namespace std;


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;

const GLfloat g_AngleSpeed = 10.0f;

ParticleSystem* ps;
Basis* g_Basis;

GlFrame::GlFrame()
{
    setWindowTitle(trUtf8("IN55-GlFrame"));
    ps = new ParticleSystem();
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

	// Chargement des shaders
    //createShader( "Shaders/color" );

    createShader( "Shaders/PerVertex" );

    cout << "Shader color: ";
    //if (useShader( "color" ))
    if (useShader( "PerVertex" ))
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
        g_Basis->draw();
//	popMatrix();

//    pushMatrix();
        ps->draw();
    popMatrix();
}


void
GlFrame::keyPressEvent( QKeyEvent* event )
{
	switch( event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

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
	}
}
