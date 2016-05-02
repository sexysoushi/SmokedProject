#ifndef PARTICLE_H
#define PARTICLE_H
#include "Common/GlFramework.h"
#include "Common/Object3D.h"
#include "shape.h"


class Particle : public Object3D
{

private:

    vec3   velocity; // vitesse orientée sur un axe
    vec3   color;    // couleur de la particule
    double       lifeTime; // durée de vie de la particule
    double       size;     // taille de la particule
    double age;

    double depth;

public:
    Particle();
    Particle(double s);
    ~Particle();

    void setColor(vec3 c);
    void setVelocity(vec3 v);
    double getTimeAlive();

    //void drawParticule();

protected:
    void drawShape();

private:
    GLfloat m_TabVertices[4*3];



//class Shape shapeParticle; //def si 2D ou 3D, si 2D def rond/carré/(triangle), si 3D def sphere/cube/(pyramide)

};

#endif // PARTICLE_H
