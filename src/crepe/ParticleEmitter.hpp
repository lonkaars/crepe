#pragma once

#include <vector>
#include "Particle.hpp"



class ParticleEmitter {
public:
    ParticleEmitter(unsigned int maxParticles, unsigned int emissionRate, unsigned int speed, unsigned int speedOffset, unsigned int angle, unsigned int angleOffset,float m_beginLifespan,float m_endLifespan);
    ~ParticleEmitter();

    Position m_position; //position of the emitter
    unsigned int m_maxParticles; //maximum number of particles
    unsigned int m_emissionRate; //rate of particle emission
    unsigned int m_speed; //base speed of the particles
    unsigned int m_speedOffset; //offset for random speed variation
    unsigned int m_minAngle; //min angle of particle emission
    unsigned int m_maxAngle; //max angle of particle emission
    float m_beginLifespan; //begin Lifespan of particle (only visual)
    float m_endLifespan; //begin Lifespan of particle

    std::vector<Particle> particles; //collection of particles

};
