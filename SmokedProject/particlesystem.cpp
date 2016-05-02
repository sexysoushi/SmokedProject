#include "particlesystem.h"

ParticleSystem::ParticleSystem()
    : rate(200.0),
      nbMax(1000.0),
      //maxTimeAlive(10.0),
      TabParticle(new Particle*[0]),
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


void ParticleSystem::update(float fDeltaTime)
{
//    for ( unsigned int i = 0; i < TabParticle.size(); ++i )
//    {
//        Particle* particle = TabParticle[i];

//        particle->age += fDeltaTime;
//        if ( particle->age > particle->lifeTime )
//        {
//            if ( m_pParticleEmitter != NULL ) EmitParticle(particle);
//            else RandomizeParticle(particle);
//        }

//        float lifeRatio = glm::saturate(particle->age / particle->lifeTime);
//        particle->velocity += ( m_Force * fDeltaTime );
//        particle->position += ( particle->velocity * fDeltaTime );
//        particle->color = m_ColorInterpolator.GetValue( lifeRatio );
//        particle->rotation = glm::lerp<float>( 0.0f, 720.0f, lifeRatio );
//        particle->size = glm::lerp<float>( 5.0f, 0.0f, lifeRatio );
//    }

//    BuildVertexBuffer();
}
