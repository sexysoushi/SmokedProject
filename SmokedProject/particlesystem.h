#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Common/GlFramework.h"
#include "Common/Object3D.h"
#include <QTimer>
#include <ctime>
#include "Common/RandomNumberGenerator.h"

struct Particle{
    vec3 position;
    vec3   velocity; // vitesse orientée sur un axe
    vec3   color;    // couleur de la particule
    double       lifeTime; // durée de vie de la particule
    double       size;     // taille de la particule
    double age;
};

class ParticleSystem : public Object3D
{

public slots:
    void addParticle();

private:
    vec3 orientation;
    double rate;
    double nbMax;
    double maxTimeAlive;
    std::vector<Particle*> TabParticle;
    bool isStarted;

    time_t timer;
    time_t currentTime;
    void updateParticleTime();
    void particleMotion();

    RandomNumberGenerator randomG;

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
