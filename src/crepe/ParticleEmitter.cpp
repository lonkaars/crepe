#include "ParticleEmitter.hpp"
#include <ctime>
#include "Particle.hpp"
#include <iostream>

ParticleEmitter::ParticleEmitter(unsigned int maxParticles, unsigned int emissionRate, unsigned int speed, unsigned int speedOffset, unsigned int angle, unsigned int angleOffset, float m_beginLifespan, float m_endLifespan)
    : m_maxParticles(maxParticles), m_emissionRate(emissionRate), m_speed(speed), m_speedOffset(speedOffset), m_position{0, 0}, m_beginLifespan(m_beginLifespan),m_endLifespan(m_endLifespan) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // initialize random seed
    std::cout << "Create emitter" << std::endl;
    m_minAngle = (360 + angle - (angleOffset % 360)) % 360; // calculate minAngle
    m_maxAngle = (360 + angle + (angleOffset % 360)) % 360; // calculate maxAngle
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
