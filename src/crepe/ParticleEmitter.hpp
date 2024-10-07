#pragma once

#include <vector>
#include "Particle.hpp"

class ParticleEmitter {
public:
    ParticleEmitter(unsigned int maxParticles, unsigned int emissionRate, unsigned int speed, unsigned int speedOffset, unsigned int angle, unsigned int angleOffset);
    struct Position { //struct to hold position
        float x;
        float y;
    };

    Position m_position; //position of the emitter
    unsigned int m_maxParticles; //maximum number of particles
    unsigned int m_emissionRate; //rate of particle emission
    unsigned int m_speed; //base speed of the particles
    unsigned int m_speedOffset; //offset for random speed variation
    unsigned int m_minAngle; //min angle of particle emission
    unsigned int m_maxAngle; //max angle of particle emission

    std::vector<Particle> particles; //collection of particles
};
