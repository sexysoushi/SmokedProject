#include "particle.h"

GLfloat g_TabColorsParticle[] =
{
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

};

GLuint indices[] =
{
  0, 1, 2, 3
};

Particle::Particle( double s):
    size(s),
    m_TabVertices {
        -s/2, -s/2, 0,
        s/2, -s/2, 0,
        s/2, s/2, 0,
        -s/2, s/2, 0
    }
{
}

Particle::Particle()
{}


Particle::~Particle()
{

}

void Particle::setColor(vec3 c)
{}

void Particle::setVelocity(vec3 v)
{}

double Particle::getTimeAlive()
{}

//void Particle::drawParticule()
//{}






void Particle::drawShape()
{
    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, m_TabVertices );

    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, g_TabColorsParticle );

    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, indices );

    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );
}
