#include "particlesystem.h"

ParticleSystem::ParticleSystem()
    : rate(200.0),
      nbMax(1000.0),
      maxTimeAlive(10.0),
      TabParticle(new Particle*[nbMax]),
      isStarted(false)
{

}


ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::start()
{

}


void ParticleSystem::stop()
{

}


void ParticleSystem::live()
{}
