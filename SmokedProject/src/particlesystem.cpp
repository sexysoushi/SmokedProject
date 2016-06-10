#include "particlesystem.h"
#include <cmath>


//////////////// PUBLIC ////////////////

/********** LIFE CYCLE ********/

ParticleSystem::ParticleSystem()
    : m_rate(5000),
      m_nbMax(50000.0),
      m_maxTimeAlive(5000.0),
      m_started(false),
      m_spread(40),
      m_speed(8),
      m_gravity(2),
      m_down(vec3{0.0f, -1.0f, 0.0f}),
      gl_positions(NULL),
      gl_velocities(NULL),
      gl_ages(NULL),
      m_pointSize(1)
{
    addParticle();

    m_orientation.x = 0;
    m_orientation.y = 1;
    m_orientation.z = 0;

    m_position.x = 0;
    m_position.y = 0;
    m_position.z = 0;

    m_randomG.initSeed(clock());

    gl_shader = "Basic";
    gl_texId = -1;

    m_transparent = true;
}

ParticleSystem::ParticleSystem(float r, int n, float t, float s, float sp, float gr, vec3 d, float p)
    : m_rate(r),
      m_nbMax(n),
      m_maxTimeAlive(t),
      m_started(false),
      m_spread(s),
      m_speed(sp),
      m_gravity(gr),
      m_down(d),
      gl_positions(NULL),
      gl_velocities(NULL),
      gl_ages(NULL),
      m_pointSize(p)
{
    ParticleSystem();
}

ParticleSystem::~ParticleSystem(){
    if(gl_positions = NULL) delete gl_positions;
    if(gl_velocities != NULL) delete gl_velocities;
    if(gl_ages != NULL) delete gl_ages;
}

/********* GETTERS / SETTERS **********/

///
/// \brief ParticleSystem::start
///     Start rendering the system
///
void ParticleSystem::start()
{
    m_started = true;
}

///
/// \brief ParticleSystem::stop
///     Stop rendering and clear data
///
void ParticleSystem::stop()
{
    m_started = false;
    clear();
}

///
/// \brief ParticleSystem::setShader
///     Set the shader program to be used for rendering
/// \param c a previously loaded shader program
///
void ParticleSystem::setShader(std::string c)
{
    gl_shader = c;
}

///
/// \brief ParticleSystem::loadTexture
///     Load texture from disk to gpu memory and get buffer id
/// \param t the relative file path
///
void ParticleSystem::loadTexture(char *t)
{
    gl_texId = Texture::loadTexture(t);
}

///
/// \brief ParticleSystem::setTransparent
///     Set the transparency of particles
/// \param b true/false
///
void ParticleSystem::setTransparent(bool b){
    m_transparent = b;
}

///
/// \brief ParticleSystem::isStarted
/// \return
///
bool ParticleSystem::isStarted(){
    return m_started;
}

///
/// \brief ParticleSystem::clear
///     Clear list of particles, buffers and arrays
///
void ParticleSystem::clear()
{
    m_TabParticle.clear();
    m_TabParticle.shrink_to_fit();

    if(gl_positions != NULL) {
        delete gl_positions;
        gl_positions == NULL;
    }

    if(gl_velocities != NULL){
        delete gl_velocities;
        gl_velocities = NULL;
    }

    if(gl_ages != NULL) {
        delete gl_ages;
        gl_ages = NULL;
    }
}

///
/// \brief ParticleSystem::draw
///     Redefined from Object3D to be able to use any shader
///     Rendering function
///
void ParticleSystem::draw()
{
    if (m_Framework->useShader( (char*)gl_shader.c_str() ))
    {
        m_Framework->computeAncillaryMatrices();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        drawShape();
    }
}


/////////////// PRIVATE //////////////


/******* Particles Life and Death ********/

///
/// \brief ParticleSystem::update
///     Update timers and manage particles life and death
///
void ParticleSystem::update()
{
    t_timeSinceLastFrame = elapsedTime(t_currentTime, std::chrono::steady_clock::now());

    t_currentTime = Clock::now();
    t_timeSinceLastTrigger = elapsedTime(t_lastTrigger, t_currentTime);

    //std::cout<<timeSinceLastTrigger<<std::endl;

    int nb = t_timeSinceLastTrigger / (1000/m_rate);

    if(nb >= 1)
    {
        t_lastTrigger = t_currentTime;
        //std::cout<<timeSinceLastTrigger<<std::endl;
        while(nb >= 1){
            addParticle();
            nb--;
        }
    }

    if(m_maxTimeAlive > 0)
        deleteDeadParticles();
}


///
/// \brief ParticleSystem::addParticle
///     Create and add a particle to the system
///         Positions are the Particle System position for now
///         Velocities are random and following a cone shaped area
///         StartTime is now
///
void ParticleSystem::addParticle()
{
    Particle* particle;
    if(m_TabParticle.size() >= m_nbMax){
        m_TabParticle.pop_front();
    }

    particle = new Particle();
    particle->position = m_position;
    particle->velocity = getRandomVector();
    particle->startTime = Clock::now();

    m_TabParticle.push_back(particle);
}

///
/// \brief ParticleSystem::deleteDeadParticles
///     Delete particles that are supposed to be dead :
///         = If a particle is too old and doesn't fit Meryn Trant's needs
///
void ParticleSystem::deleteDeadParticles(){

    for(unsigned int i=0; i<m_TabParticle.size(); i++){
        Particle* p = m_TabParticle[i];
        if(p != NULL && elapsedTime(p->startTime, t_currentTime) > m_maxTimeAlive){
            m_TabParticle.erase(m_TabParticle.begin()+i);
            m_TabParticle.shrink_to_fit();
        }
    }
}

/******* OPERATIONS ********/

///
/// \brief ParticleSystem::buildGLBuffers
///     Build vertices data buffers to be passed to the shader
///     This includes :
///         Relative positions
///             For now, it's all (0,0,0)
///             Consider it to be an offset for particle drawing, as true positions are calculated
///             in the shader;
///         Velocities
///         Ages
///
void ParticleSystem::buildGLBuffers(){

    if(gl_positions != NULL) delete gl_positions;
    gl_positions = new float[m_TabParticle.size()*3];

    if(gl_velocities != NULL) delete gl_velocities;
    gl_velocities = new float[m_TabParticle.size()*3];

    if(gl_ages != NULL) delete gl_ages;
    gl_ages = new float[m_TabParticle.size()];

    for(unsigned int i=0; i<m_TabParticle.size(); i++){
        Particle* p = m_TabParticle[i];

        gl_positions[3*i] = p->position.x;
        gl_positions[3*i+1] = p->position.y;
        gl_positions[3*i+2] = p->position.z;

        gl_velocities[3*i] = p->velocity.x;
        gl_velocities[3*i+1] = p->velocity.y;
        gl_velocities[3*i+2] = p->velocity.z;

        gl_ages[i] = elapsedTime(p->startTime, Clock::now()) / 1000.0f;

        //std::cout<<velocities[3*i]<<" "<<velocities[3*i+1]<<" "<<velocities[3*i+2]<<std::endl;
        //std::cout << i << " : " << ages[i] << std::endl;
    }
}


///
/// \brief ParticleSystem::getRandomVector
///     Build a random vector on a cone of angle m_spread
/// \return a random vector
///
vec3 ParticleSystem::getRandomVector()
{
    vec3 v;

    float rAngle = m_randomG.getRandomNumber(m_spread) * M_PI/180.0f;
    float disAngle = m_randomG.getRandomNumber(2 * M_PI);

    if(gl_shader == "Firework")
        v.y = rAngle*std::cos(disAngle);
    else
        v.y = std::cos(rAngle);
    v.x = rAngle*std::cos(disAngle);
    v.z = rAngle*std::sin(disAngle);

    return v;
}

///
/// \brief ParticleSystem::elapsedTime
///     Get elapsed time between two time points
/// \param start
/// \param end
/// \return milliseconds
///
float ParticleSystem::elapsedTime(Clock::time_point start, Clock::time_point end){
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

///
/// \brief ParticleSystem::drawShape
///     Main rendering function
///
void ParticleSystem::drawShape()
{
    if(!isStarted())
        return;

    update();
    buildGLBuffers();

    if(m_transparent)
        glDisable(GL_DEPTH_TEST);


    // Uniform data

    GLuint s = glGetUniformLocation(m_Framework->getCurrentShaderId(), "speed");
    glUniform1f(s, m_speed);

    GLuint ps = glGetUniformLocation(m_Framework->getCurrentShaderId(), "size");
    glUniform1f(ps, m_pointSize);

    GLuint g = glGetUniformLocation(m_Framework->getCurrentShaderId(), "gravity");
    glUniform1f(g, m_gravity);

    GLuint d = glGetUniformLocation(m_Framework->getCurrentShaderId(), "down");
    glUniform3f(d, m_down.x, m_down.y, m_down.z);


    // vertex data

    GLint p = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( p );
    glVertexAttribPointer( p, 3, GL_FLOAT, GL_FALSE, 0, gl_positions );

    GLint v = glGetAttribLocation( m_Framework->getCurrentShaderId(), "velocity" );
    glEnableVertexAttribArray( v );
    glVertexAttribPointer( v, 3, GL_FLOAT, GL_TRUE, 0, gl_velocities );

    GLint a = glGetAttribLocation( m_Framework->getCurrentShaderId(), "age" );
    glEnableVertexAttribArray( a );
    glVertexAttribPointer( a, 1, GL_FLOAT, GL_FALSE, 0, gl_ages );


    // texture loading, drawing

    if(gl_texId != -1)
    {
        glEnable(GL_POINT_SPRITE);
        glUniform1i(gl_texId,0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gl_texId);
        glEnable(GL_TEXTURE_2D);
        glDrawArrays(GL_POINTS,0, m_TabParticle.size());
        glDisable(GL_TEXTURE_2D);
    }
    else
        glDrawArrays(GL_POINTS,0, m_TabParticle.size());

    // deallocation

    glDisableVertexAttribArray( v );
    glDisableVertexAttribArray( p );
    glDisableVertexAttribArray( a );

    if(m_transparent)
        glEnable(GL_DEPTH_TEST);

}

