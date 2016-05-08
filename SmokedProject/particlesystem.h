#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Common/GlFramework.h"
#include "Common/Object3D.h"

struct Particle{
    vec3 position;
    vec3   velocity; // vitesse orientée sur un axe
    vec3   color;    // couleur de la particule
    double       lifeTime; // durée de vie de la particule
    double       size;     // taille de la particule
    double age;
};

class ParticleSystem
{
private:
    double rate;
    double nbMax;
    double maxTreeAlive;
    Particle** TabParticle;
    bool isStarted;

public:
    ParticleSystem();
    ~ParticleSystem();

    void start();
    void stop();
    void live();
    void update(float fDeltaTime);
};

#endif // PARTICLESYSTEM_H
