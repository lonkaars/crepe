#include "ParticleEmitter.hpp"
#include <ctime>

ParticleEmitter::ParticleEmitter(unsigned int maxParticles, unsigned int emissionRate, unsigned int speed, unsigned int speedOffset, unsigned int angle, unsigned int angleOffset, float m_beginLifespan, float m_endLifespan)
    : m_maxParticles(maxParticles), m_emissionRate(emissionRate), m_speed(speed), m_speedOffset(speedOffset), m_position{0, 0}, m_beginLifespan(m_beginLifespan),m_endLifespan(m_endLifespan) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // initialize random seed

    m_minAngle = (360 + angle - (angleOffset % 360)) % 360; // calculate minAngle
    m_maxAngle = (360 + angle + (angleOffset % 360)) % 360; // calculate maxAngle

}