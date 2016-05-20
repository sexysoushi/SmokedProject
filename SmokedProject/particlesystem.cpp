#include "particlesystem.h"
#include <iostream>

ParticleSystem::ParticleSystem()
    : rate(200.0),
      nbMax(100.0),
      maxTimeAlive(1000.0),
      isStarted(false),
      timer(clock()),
      currentTime(clock())
{
    addParticle();

    orientation.x = 0;
    orientation.y = 1;
    orientation.z = 0;

    position.x = 0;
    position.y = 0;
    position.z = 0;

    g_cube = new Cube(1.0);
}

ParticleSystem::~ParticleSystem(){}

void ParticleSystem::start()
{
    isStarted = true;
}


void ParticleSystem::stop()
{
    isStarted = false;
}


void ParticleSystem::live()
{
    if(isStarted)
    {
        currentTime = clock()/(double)(CLOCKS_PER_SEC/1000);
        double diff = currentTime-timer;
        std::cout<<"time diff "<<diff<<"\n";
        if(diff > (1/rate))
        {
            timer = clock()/(double)(CLOCKS_PER_SEC/1000);
            addParticle();
        }
    }

}

void ParticleSystem::particleMotion(Particle* particle)
{
//   particle->position.x += randomG.getRandomNumber(2)*(time(NULL) - currentTime);
//   particle->position.z += randomG.getRandomNumber(2)*(time(NULL) - currentTime);
//   particle->position.y += 0.1*(time(NULL) - currentTime);
}

void ParticleSystem::updateParticleTime(Particle* particle)
{
   //particle->age = particle->age + (time(NULL) - currentTime);
//   std::cout<<"age particle "<<particle->age<<"\n";
//   if(particle->age > maxTimeAlive)
//   {
//        resetParticle(particle);
//   }

}

void ParticleSystem::addParticle()
{
    if(TabParticle.size() <= nbMax)
    {
        Particle* particle= new Particle();
        particle->position = position;
        //particle->age = 0;
        particle->lifeTime = maxTimeAlive;
        particle->velocity = orientation;
        particle->color.x = 1.0;
        particle->color.y = 1.0;
        particle->color.z = 1.0;
        particle->size = 6;
        TabParticle.push_back(particle);
    }

}

void ParticleSystem::resetParticle(Particle* particle)
{
    particle->position = position;
    //particle->age = 0;
    particle->lifeTime = maxTimeAlive;
    particle->velocity = orientation;
    particle->color.x = 1.0;
    particle->color.y = 1.0;
    particle->color.z = 1.0;
    particle->size = 6;
}


void ParticleSystem::drawShape()
{

    for ( unsigned int i = 0; i < TabParticle.size(); ++i )
       {
           Particle* particle = TabParticle[i];
           updateParticleTime( particle);
           particleMotion(particle);

           std::cout<<"particle "<<i+1<<"/"<<TabParticle.size()<<"\n";
           m_Framework->pushMatrix();
           m_Framework->translate(particle->position.x, particle->position.y+i, particle->position.z);
           g_cube->draw();
           m_Framework->popMatrix();
        }
}

