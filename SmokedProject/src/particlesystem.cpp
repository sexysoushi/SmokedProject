#include "particlesystem.h"
#include <cmath>

ParticleSystem::ParticleSystem()
    : rate(1000),
      nbMax(50000.0),
      maxTimeAlive(3000.0),
      started(false),
      spread(40),
      speed(8),
      gravity(2),
      down(vec3{0.0f, -1.0f, 0.0f}),
      positions(NULL),
      velocities(NULL),
      ages(NULL)
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

ParticleSystem::ParticleSystem(float r, int n, float t, float s, float sp, float gr, vec3 d)
    : rate(r),
      nbMax(n),
      maxTimeAlive(t),
      started(false),
      spread(s),
      speed(sp),
      gravity(gr),
      down(d),
      positions(NULL),
      velocities(NULL),
      ages(NULL)
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

ParticleSystem::ParticleSystem(ParticleSystem *p)
    :ParticleSystem(p->getRate(), p->getNbMax(), p->getMaxTimeAlive(), p->getSpread(), p->getSpeed(), p->getGravity(), p->getDown())
{}

ParticleSystem::~ParticleSystem(){
    if(positions = NULL) delete positions;
    if(velocities != NULL) delete velocities;
    if(ages != NULL) delete ages;
}

void ParticleSystem::start()
{
    started = true;
}


void ParticleSystem::stop()
{
    started = false;
    clear();
}

bool ParticleSystem::isStarted(){
    return started;
}


void ParticleSystem::lockMutex(){
    //mut->lock();
}

void ParticleSystem::unlockMutex(){
    //mut->unlock();
}

void ParticleSystem::clear()
{
    TabParticle.clear();
    TabParticle.shrink_to_fit();

    if(positions != NULL) {
        delete positions;
        positions == NULL;
    }

    if(velocities != NULL){
        delete velocities;
        velocities = NULL;
    }

    if(ages != NULL) {
        delete ages;
        ages = NULL;
    }
}

float ParticleSystem::timeInterval(Clock::time_point start, Clock::time_point end){
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void ParticleSystem::setRate(double r){
    nbMax = r;
}

float ParticleSystem::getRate() const
{
    return rate;
}


int ParticleSystem::getNbMax() const
{
    return nbMax;
}

void ParticleSystem::setNbMax(int value)
{
    nbMax = value;
}

float ParticleSystem::getMaxTimeAlive() const
{
    return maxTimeAlive;
}

void ParticleSystem::setMaxTimeAlive(float value)
{
    maxTimeAlive = value;
}

float ParticleSystem::getSpread() const
{
    return spread;
}

void ParticleSystem::setSpread(float value)
{
    spread = value;
}

float ParticleSystem::getSpeed() const
{
    return speed;
}

float ParticleSystem::setSpeed(float value)
{
    speed = value;
}

float ParticleSystem::getGravity() const
{
    return gravity;
}

float ParticleSystem::setGravity(float value)
{
    gravity = value;
}

vec3 ParticleSystem::getDown() const
{
    return down;
}

void ParticleSystem::setDown(vec3 v){
    down = v;
}

// life and death of particles
void ParticleSystem::updateTime()
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

    if(maxTimeAlive > 0)
        deleteDeadParticles();
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

void ParticleSystem::deleteDeadParticles(){

    for(unsigned int i=0; i<TabParticle.size(); i++){
        Particle* p = TabParticle[i];
        if(p != NULL && timeInterval(p->startTime, currentTime) > maxTimeAlive){
            TabParticle.erase(TabParticle.begin()+i);
            TabParticle.shrink_to_fit();
        }
    }
}


void ParticleSystem::buildArrays(){

    //deleteDeadParticles();

    if(positions != NULL) delete positions;
    positions = new float[TabParticle.size()*3];

    if(velocities != NULL) delete velocities;
    velocities = new float[TabParticle.size()*3];

    if(ages != NULL) delete ages;
    ages = new float[TabParticle.size()];

    for(unsigned int i=0; i<TabParticle.size(); i++){
        Particle* p = TabParticle[i];

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

//vec3 ParticleSystem::randomVector()
//{
//    vec3 v;
////    v.x = 0;
////    v.y = 1;
////    v.z = 0;

////    //float rAngle = M_PI * spread / 180.0f;
////    float rAngle = randomG.getRandomNumber(spread) * M_PI/180.0;

////    if(randomG.getFloat32() > 1.5f)
////    {
////        // rotation du vecteur jusqu'au spread max (selon l'axe z arbitraire)
////        v.x = -v.y * std::sin(rAngle);
////        v.y = v.y * std::cos(rAngle);
////    }
////    else
////    {
////        // rotation du vecteur jusqu'au spread max (selon l'axe x arbitraire)
////        v.y = v.y * std::cos(rAngle);
////        v.z = v.y * std::sin(rAngle);
////    }

////    // rotation <2.PI autour de y
////     float disAngle = randomG.getRandomNumber(2 * M_PI);
////    //disAngle += 0.15;
////    v.x = v.z * std::sin(disAngle) + v.x * std::cos(disAngle);
////    v.z = v.z * std::cos(disAngle) - v.x * std::sin(disAngle);

//    float rAngle = randomG.getRandomNumber(spread) * M_PI/180.0f;
//    float disAngle = randomG.getRandomNumber(2 * M_PI);

//    v.y = std::cos(rAngle);
//    v.x = rAngle*std::cos(disAngle);
//    v.z = rAngle*std::sin(disAngle);

//    return v;
//}


//Pour l'effet FIREWORK
vec3 ParticleSystem::randomVector()
{
    vec3 v;
    float rAngle = randomG.getRandomNumber(spread) * M_PI/180.0f;
    float disAngle = randomG.getRandomNumber(2 * M_PI);

    v.y = rAngle*std::cos(disAngle);
    v.x = rAngle*std::cos(disAngle);
    v.z = rAngle*std::sin(disAngle);

    return v;
}

void ParticleSystem::drawShape()
{
    if(!started)
        return;

    //std::cout<<TabParticle.size()<<std::endl;
    updateTime();
    buildArrays();

//    GLuint mv = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MV");
//    m_Framework->transmitMV(mv);

    GLuint s = glGetUniformLocation(m_Framework->getCurrentShaderId(), "speed");
    glUniform1f(s, speed);

    GLuint g = glGetUniformLocation(m_Framework->getCurrentShaderId(), "gravity");
    glUniform1f(g, gravity);

    GLuint d = glGetUniformLocation(m_Framework->getCurrentShaderId(), "down");
    glUniform3f(d, down.x, down.y, down.z);

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

