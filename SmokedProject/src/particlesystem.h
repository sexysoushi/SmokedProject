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
#include <QMutex>

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
    int nbMax;
    float maxTimeAlive;
    float spread;

    float speed;
    float gravity;
    vec3 down;

    bool started;

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

    QMutex* mut;

    void particleMotion(Particle* particle);
    void addParticle();
    void resetParticle(Particle* particle);

    void buildArrays();
    vec3 randomVector();

    float timeInterval(Clock::time_point start, Clock::time_point end);


    void deleteDeadParticles();

public:
    ParticleSystem();
    ParticleSystem(float r, int n, float t, float s, float sp, float gr, vec3 d);
    ParticleSystem(ParticleSystem* p);

    ~ParticleSystem();

    void start();
    void stop();

    void updateTime();

    bool isStarted();

    void lockMutex();
    void unlockMutex();

    void clear();

    void setRate(double r);
    float getRate() const;

    int getNbMax() const;
    void setNbMax(int value);

    float getMaxTimeAlive() const;
    void setMaxTimeAlive(float value);

    float getSpread() const;
    void setSpread(float value);

    float getSpeed() const;
    float setSpeed(float value);

    float getGravity() const;
    float setGravity(float value);

    vec3 getDown() const;
    void setDown(vec3 v);

protected:
    void drawShape();

};

#endif // PARTICLESYSTEM_H