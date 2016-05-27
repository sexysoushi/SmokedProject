#include "src/Common/Shapes/cube.h"
#include "cube.h"



GLfloat g_TabColorsCube[] =
{
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
};

GLuint indices1[] =
{
  0,4,6,2,3,1,5,4
};

GLuint indices2[] =
{
  7,3,2,6,4,5,1,3
};

Cube::Cube( GLfloat length ):
    m_TabVertices {
        0,0,0,
        0,0,length,
        0,length,0,
        0,length,length,
        length,0,0,
        length,0,length,
        length,length,0,
        length,length,length
    }
{
}


void Cube::drawShape()
{
    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, m_TabVertices );

    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, g_TabColorsCube );

    glDrawElements( GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, indices1 );

    glDrawElements( GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, indices2 );

    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );
}
