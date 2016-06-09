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
    // particle system parameters
    vec3 position;
    vec3 orientation;
    float rate;
    int nbMax;
    float maxTimeAlive;
    float spread;

    float speed;
    float gravity;
    vec3 down;

    bool started;

    // particles array
    std::deque<Particle*> TabParticle;

    // GL data
    float* positions;
    float* velocities;
    float* ages;

    char* shader;
    QImage texture;

    // timers
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

    void deleteDeadParticles();
    void updateTime();


public:
    ParticleSystem();
    ParticleSystem(float r, int n, float t, float s, float sp, float gr, vec3 d);

    ~ParticleSystem();

    void start();
    void stop();

    bool isStarted();

    void clear();

    //void draw();

protected:
    void drawShape();

};

#endif // PARTICLESYSTEM_H
