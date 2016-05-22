#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Common/GlFramework.h"
#include "Common/Object3D.h"
#include "Common/RandomNumberGenerator.h"
//#include "Shapes/cube.h"

#include <ctime>
#include <chrono>
#include <iostream>
#include <deque>

typedef std::chrono::steady_clock Clock;

struct Particle{
    vec3   position;
    vec3   velocity; // vitesse orientée sur un axe
    //vec3   color;    // couleur de la particule
    //double size;     // taille de la particule
    Clock::time_point startTime;
};

class ParticleSystem : public Object3D
{
private:
    vec3 position;
    vec3 orientation;
    float rate;
    float nbMax;
    float maxTimeAlive;
    float spread;

    //shader const
    const float speed;
    const float gravity;

    bool isStarted;

    float disAngle;

    std::deque<Particle*> TabParticle;

    float* positions;
    float* velocities;
    float* ages;

    Clock::time_point first = std::chrono::steady_clock::now();
    Clock::time_point lastTrigger = first;
    Clock::time_point currentTime = first;
    float timeSinceLastTrigger;
    float timeSinceLastFrame;

    RandomNumberGenerator randomG;

    void particleMotion(Particle* particle);
    void addParticle();
    void resetParticle(Particle* particle);

    void buildArrays();
    vec3 randomVector();

    float timeInterval(Clock::time_point start, Clock::time_point end);


public:
    ParticleSystem();
    ~ParticleSystem();

    void start();
    void stop();

    void updateTime();

protected:
    void drawShape();

};

#endif // PARTICLESYSTEM_H
