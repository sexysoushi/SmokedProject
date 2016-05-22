#include "particlesystem.h"

ParticleSystem::ParticleSystem()
    : rate(0.1),
      nbMax(100.0),
      maxTimeAlive(1000.0),
      isStarted(false),
      lastTrigger(clock()/(double)(CLOCKS_PER_SEC/1000)),
      currentTime(clock())
{
    addParticle();

    first = clock()/(double)(CLOCKS_PER_SEC/1000);

    orientation.x = 0;
    orientation.y = 1;
    orientation.z = 0;

    position.x = 0;
    position.y = 0;
    position.z = 0;

    //g_cube = new Cube(1.0);
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
        timeSinceLastFrame = (clock() - currentTime)/(double)(CLOCKS_PER_SEC/1000);
        currentTime = clock();
        timeSinceLastTrigger = (currentTime-lastTrigger)/(double)(CLOCKS_PER_SEC/1000);

        //std::cout<<timeSinceLastTrigger<<std::endl;
        std::cout<<clock()<<std::endl;

        if(timeSinceLastTrigger > rate)
        {
            lastTrigger = clock();
            addParticle();
        }
    }

}

void ParticleSystem::particleMotion(Particle* particle)
{
//   particle->position.x += randomG.getRandomNumber(2)*(time(NULL) - currentTime);
//   particle->position.z += randomG.getRandomNumber(2)*(time(NULL) - currentTime);
//   particle->position.y += 0.1*(time(NULL) - currentTime);
    particle->position.y += 0.1;
}


void ParticleSystem::addParticle()
{
    if(TabParticle.size() <= nbMax)
    {
        Particle* particle= new Particle();
        particle->position = position;
        particle->lifeTime = maxTimeAlive;
        particle->velocity = orientation;
        particle->velocity.x += 0.3;
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

void ParticleSystem::buildArrays(){
    //if(positions != NULL) delete positions;
    positions = new float[TabParticle.size()*3];

    //if(velocities != NULL) delete velocities;
    velocities = new float[TabParticle.size()*3];

    for(int i=0; i<TabParticle.size(); i++){
        Particle* p = TabParticle[i];

        particleMotion(p);

        positions[3*i] = p->position.x;
        positions[3*i+1] = p->position.y;
        positions[3*i+2] = p->position.z;

        //std::cout<<positions[3*i]<<" "<<positions[3*i+1]<<" "<<positions[3*i+2]<<std::endl;

        velocities[3*i] = p->velocity.x;
        velocities[3*i+1] = p->velocity.y;
        velocities[3*i+2] = p->velocity.z;
    }
}


void ParticleSystem::drawShape()
{
    //std::cout<<TabParticle.size()<<std::endl;

    buildArrays();

    int t = glGetUniformLocation(m_Framework->getCurrentShaderId(), "time");
    glUniform1d(t, timeSinceLastFrame);

    GLint p = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( p );

    GLint v = glGetAttribLocation( m_Framework->getCurrentShaderId(), "velocity" );
    glEnableVertexAttribArray( v );

    glVertexAttribPointer( p, 3, GL_FLOAT, GL_FALSE, 0, positions );
    glVertexAttribPointer( v, 3, GL_FLOAT, GL_FALSE, 0, velocities );

    glDrawArrays(GL_POINTS,0,TabParticle.size());

    glDisableVertexAttribArray( v );
    glDisableVertexAttribArray( p );
}

