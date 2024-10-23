#pragma once

#include <vector>
#include "Particle.h"
#include <cstdint>
#include "Component.h"
#

namespace crepe {

class ParticleEmitter : public Component {
public:
    ParticleEmitter(uint32_t gameObjectId, uint32_t maxParticles, uint32_t emissionRate, uint32_t speed, uint32_t speedOffset, uint32_t angle, uint32_t angleOffset,float m_beginLifespan,float m_endLifespan);
    ~ParticleEmitter();

    Position m_position; //position of the emitter
	uint32_t m_maxParticles; //maximum number of particles
	uint32_t m_emissionRate; //rate of particle emission
	uint32_t m_speed; //base speed of the particles
	uint32_t m_speedOffset; //offset for random speed variation
	uint32_t m_minAngle; //min angle of particle emission
	uint32_t m_maxAngle; //max angle of particle emission
    float m_beginLifespan; //begin Lifespan of particle (only visual)
    float m_endLifespan; //begin Lifespan of particle

    std::vector<Particle> particles; //collection of particles

};

}


