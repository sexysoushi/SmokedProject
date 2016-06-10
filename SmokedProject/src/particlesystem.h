#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H


#include "Common/GlFramework.h"
#include "Common/Object3D.h"
#include "Common/RandomNumberGenerator.h"
#include "Common/Vectors.h"
#include "Texture.h"

#include <ctime>
#include <chrono>
#include <iostream>
#include <deque>
#include <QImage>
#include <QGLWidget>

// time handler type definition
typedef std::chrono::steady_clock Clock;

// Particle object definition
struct Particle{
    vec3   position;
    vec3   velocity; // speed * normalized direction
    Clock::time_point startTime;
};

class ParticleSystem : public Object3D
{

private:
    // particle system parameters
    vec3 m_position;
    vec3 m_orientation;
    float m_rate;
    int m_nbMax;
    float m_maxTimeAlive;
    float m_spread;
    float m_pointSize;

    float m_speed;
    float m_gravity;
    vec3 m_down;

    bool m_started;

    bool m_transparent;

    // particles array
    std::deque<Particle*> m_TabParticle;

    // GL data
    float* gl_positions;
    float* gl_velocities;
    float* gl_ages;

    std::string gl_shader;
    GLuint gl_texId;

    // timers
    Clock::time_point t_first = std::chrono::steady_clock::now();
    Clock::time_point t_lastTrigger = t_first;
    Clock::time_point t_currentTime = t_first;
    float t_timeSinceLastTrigger;
    float t_timeSinceLastFrame;

    RandomNumberGenerator m_randomG;

    // operations
    void update();
    void addParticle();
    void deleteDeadParticles();

    void buildGLBuffers();
    vec3 getRandomVector();

    float elapsedTime(Clock::time_point start, Clock::time_point end);

    void drawShape();

public:
    ParticleSystem();
    ParticleSystem(float r, int n, float t, float s, float sp, float gr, vec3 d, float p);

    ~ParticleSystem();

    // life cycle
    void start();
    void stop();

    bool isStarted();

    void clear();

    // parameters setters
    void setShader(std::string s);
    void loadTexture(char* t);
    void setTransparent(bool b);

    // redefinition from Object3D
    void draw();
};

#endif // PARTICLESYSTEM_H
