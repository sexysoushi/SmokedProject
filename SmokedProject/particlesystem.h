#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "particle.h"

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
};

#endif // PARTICLESYSTEM_H
