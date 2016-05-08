#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Common/GlFramework.h"
#include "Common/Object3D.h"
#include <ctime>
#include "Common/RandomNumberGenerator.h"
#include "Shapes/Cubes.h"
#include "Shapes/cube.h"

struct Particle{
    vec3 position;
    vec3   velocity; // vitesse orientée sur un axe
    vec3   color;    // couleur de la particule
    double lifeTime; // durée de vie de la particule
    double size;     // taille de la particule
    double startTime;
};

class ParticleSystem : public Object3D
{
private:
    vec3 position;
    vec3 orientation;
    double rate;
    double nbMax;
    double maxTimeAlive;
    std::vector<Particle*> TabParticle;
    bool isStarted;

    clock_t timer;
    clock_t currentTime;


    void updateParticleTime(Particle* particle);
    void particleMotion(Particle* particle);
    void addParticle();
    void resetParticle(Particle* particle);

    RandomNumberGenerator randomG;
    Cube* g_cube;

public:
    ParticleSystem();
    ~ParticleSystem();

    void start();
    void stop();
    void live();

protected:
    void drawShape();

};

#endif // PARTICLESYSTEM_H
