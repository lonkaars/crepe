#include "ParticleEmitter.h"
#include <ctime>
#include "Particle.h"
#include <iostream>

using namespace crepe;

ParticleEmitter::ParticleEmitter(uint32_t maxParticles, uint32_t emissionRate, uint32_t speed, uint32_t speedOffset, uint32_t angle, uint32_t angleOffset, float m_beginLifespan, float m_endLifespan)
    : m_maxParticles(maxParticles), m_emissionRate(emissionRate), m_speed(speed), m_speedOffset(speedOffset), m_position{0, 0}, m_beginLifespan(m_beginLifespan),m_endLifespan(m_endLifespan) {
    std::srand(static_cast<uint32_t>(std::time(nullptr))); // initialize random seed
    std::cout << "Create emitter" << std::endl;
    m_minAngle = (360 + angle - (angleOffset % 360)) % 360; // calculate minAngle
    m_maxAngle = (360 + angle + (angleOffset % 360)) % 360; // calculate maxAngle
	m_position.x = 400;
	m_position.y = 400;
    for (size_t i = 0; i < m_maxParticles; i++)
    {
        this->particles.emplace_back();
    }
    
}

ParticleEmitter::~ParticleEmitter() {
    std::vector<Particle>::iterator it = this->particles.begin();
        while (it != this->particles.end()) {
            it = this->particles.erase(it);
        }
}
