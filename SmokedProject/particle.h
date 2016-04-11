#ifndef PARTICLE_H
#define PARTICLE_H

#include "GlWindow.h"

class particle
{
public:
    particle();

double lifetime; //la durée de vie d’une particule
double size; //taille particule (sprite ou voxel)

//Vec3f position; //position de la particule
//Vec3f velocity; //vitesse orientée sur un axe
//Vec3f Color; //couleur de la particule

//class Shape shapeParticle; //def si 2D ou 3D, si 2D def rond/carré/(triangle), si 3D def sphere/cube/(pyramide)

};

#endif // PARTICLE_H
