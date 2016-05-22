#include "particlesystem.h"

ParticleSystem::ParticleSystem()
    : rate(1000),
      nbMax(50000.0),
      maxTimeAlive(1000.0),
      isStarted(false),
      spread(40),
      positions(NULL),
      velocities(NULL),
      ages(NULL),
      speed(8),
      gravity(1.8)
{
    addParticle();

    orientation.x = 0;
    orientation.y = 1;
    orientation.z = 0;

    position.x = 0;
    position.y = 0;
    position.z = 0;

    disAngle=0;

    randomG.initSeed(clock());
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

float ParticleSystem::timeInterval(Clock::time_point start, Clock::time_point end){
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void ParticleSystem::updateTime()
{
    if(isStarted)
    {
        timeSinceLastFrame = timeInterval(currentTime, std::chrono::steady_clock::now());

        currentTime = Clock::now();
        timeSinceLastTrigger = timeInterval(lastTrigger, currentTime);

        //std::cout<<timeSinceLastTrigger<<std::endl;

        int nb = timeSinceLastTrigger / (1000/rate);

        if(nb >= 1)
        {
            lastTrigger = currentTime;
            //std::cout<<timeSinceLastTrigger<<std::endl;
            while(nb >= 1){
                addParticle();
                nb--;
            }
        }
    }

}

void ParticleSystem::addParticle()
{
    Particle* particle;
    if(TabParticle.size() >= nbMax){
        TabParticle.pop_front();
    }

    particle = new Particle();
    particle->position = position;
    particle->velocity = randomVector();
    particle->startTime = Clock::now();

    TabParticle.push_back(particle);
}

void ParticleSystem::buildArrays(){
    if(positions != NULL) delete positions;
    positions = new float[TabParticle.size()*3];

    if(velocities != NULL) delete velocities;
    velocities = new float[TabParticle.size()*3];

    if(ages != NULL) delete ages;
    ages = new float[TabParticle.size()];

    for(int i=0; i<TabParticle.size(); i++){
        Particle* p = TabParticle[i];

        //particleMotion(p);

        positions[3*i] = p->position.x;
        positions[3*i+1] = p->position.y;
        positions[3*i+2] = p->position.z;

        velocities[3*i] = p->velocity.x;
        velocities[3*i+1] = p->velocity.y;
        velocities[3*i+2] = p->velocity.z;

        ages[i] = timeInterval(p->startTime, Clock::now()) / 1000.0f;

        //std::cout<<velocities[3*i]<<" "<<velocities[3*i+1]<<" "<<velocities[3*i+2]<<std::endl;
        //std::cout << i << " : " << ages[i] << std::endl;
    }
}

vec3 ParticleSystem::randomVector()
{
    vec3 v;
    v.x = 0;
    v.y = 1;
    v.z = 0;

//    //float rAngle = M_PI * spread / 180.0f;
//    float rAngle = randomG.getRandomNumber(spread) * M_PI/180.0;

//    if(randomG.getFloat32() > 1.5f)
//    {
//        // rotation du vecteur jusqu'au spread max (selon l'axe z arbitraire)
//        v.x = -v.y * std::sin(rAngle);
//        v.y = v.y * std::cos(rAngle);
//    }
//    else
//    {
//        // rotation du vecteur jusqu'au spread max (selon l'axe x arbitraire)
//        v.y = v.y * std::cos(rAngle);
//        v.z = v.y * std::sin(rAngle);
//    }

//    // rotation <2.PI autour de y
//     float disAngle = randomG.getRandomNumber(2 * M_PI);
//    //disAngle += 0.15;
//    v.x = v.z * std::sin(disAngle) + v.x * std::cos(disAngle);
//    v.z = v.z * std::cos(disAngle) - v.x * std::sin(disAngle);

    float rAngle = randomG.getRandomNumber(spread) * M_PI/180.0f;
    float disAngle = randomG.getRandomNumber(2 * M_PI);

    v.y = std::cos(rAngle);
    v.x = rAngle*std::cos(disAngle);
    v.z = rAngle*std::sin(disAngle);

    return v;
}


void ParticleSystem::drawShape()
{
    //std::cout<<TabParticle.size()<<std::endl;
    buildArrays();

    int s = glGetUniformLocation(m_Framework->getCurrentShaderId(), "speed");
    glUniform1f(s, speed);

    int g = glGetUniformLocation(m_Framework->getCurrentShaderId(), "gravity");
    glUniform1f(g, gravity);

    GLint p = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( p );

    GLint v = glGetAttribLocation( m_Framework->getCurrentShaderId(), "velocity" );
    glEnableVertexAttribArray( v );

    GLint a = glGetAttribLocation( m_Framework->getCurrentShaderId(), "age" );
    glEnableVertexAttribArray( a );

    glVertexAttribPointer( p, 3, GL_FLOAT, GL_FALSE, 0, positions );
    glVertexAttribPointer( v, 3, GL_FLOAT, GL_TRUE, 0, velocities );
    glVertexAttribPointer( a, 1, GL_FLOAT, GL_FALSE, 0, ages );

    glDrawArrays(GL_POINTS,0,TabParticle.size());

    glDisableVertexAttribArray( v );
    glDisableVertexAttribArray( p );
    glDisableVertexAttribArray( a );
}

