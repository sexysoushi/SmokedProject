#include "particlesystem.h"

ParticleSystem::ParticleSystem()
    : rate(200.0),
      nbMax(1000.0),
      maxTimeAlive(10.0),
      isStarted(false),
      timer(time(NULL)),
      currentTime(time(NULL))
{
    orientation.x = 0;
    orientation.y = 1;
    orientation.z = 0;

    position.x = 0;
    position.y = 0;
    position.z = 0;
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
        updateParticleTime();
        time_t curTime = time(NULL);
        double diff = difftime(timer, curTime);
        if(diff > (1/rate))
        {
            timer = time(NULL);
            addParticle();
        }
        particleMotion();
    }

}

void ParticleSystem::particleMotion()
{
    for ( unsigned int i = 0; i < TabParticle.size(); ++i )
    {
           Particle* particle = TabParticle[i];
           particle->position.x += randomG.getRandomNumber(0.10)*(time(NULL) - currentTime);
           particle->position.y += 0.1*(time(NULL) - currentTime);
    }
}

void ParticleSystem::updateParticleTime()
{
    for ( unsigned int i = 0; i < TabParticle.size(); ++i )
       {
           Particle* particle = TabParticle[i];
           particle->age = particle->age + (time(NULL) - currentTime);
           if(particle->age > maxTimeAlive)
           {
               TabParticle[i] = NULL;
               delete particle;
           }
    }

}

void ParticleSystem::addParticle()
{
    if(TabParticle.size() <= nbMax)
    {
        Particle* particle= new Particle;
        particle->position = position;
        particle->age = 0;
        particle->lifeTime = maxTimeAlive;
        particle->velocity = orientation;
        particle->color.x = 1.0;
        particle->color.y = 1.0;
        particle->color.z = 1.0;
        particle->size = 6;
        TabParticle.push_back(particle);
    }

}


void ParticleSystem::drawShape()
{
    for ( unsigned int i = 0; i < TabParticle.size(); ++i )
       {
           Particle* particle = TabParticle[i];
           m_Framework->pushMatrix();
           m_Framework->translate(particle->position.x, particle->position.y, particle->position.z);
//           glBegin(GL_POINTS);
//           glVertex3f(particle->position.x, particle->position.y, particle->position.z);
//           glEnd();

           glBegin(GL_QUADS);
           glColor3f(1, 1, 1);
           glVertex3f(particle->size/2, particle->size/2, 0);
           glVertex3f(-particle->size/2, particle->size/2, 0);
           glVertex3f(-particle->size/2, -particle->size/2, 0);
           glVertex3f(particle->size/2, -particle->size/2, 0);
           glEnd();
           m_Framework->popMatrix();
        }
}
