#pragma once

#include <vector>
#include "Particle.hpp"

class ParticleEmitter {
public:
    ParticleEmitter(unsigned int maxParticles, unsigned int emissionRate, unsigned int speed, unsigned int speedOffset, unsigned int angle, unsigned int angleOffset);
    void update(float deltaTime); // Keep deltaTime as float
    const std::vector<Particle>& getParticles() const; //returns the collection of particles
    void setPosition(int x, int y); //sets the position of the emitter
private:
    void emitParticle(); //emits a new particle

    struct Position { //struct to hold position
        int x;
        int y;
    };

    Position m_position; //position of the emitter
    unsigned int m_maxParticles; //maximum number of particles
    unsigned int m_emissionRate; //rate of particle emission
    float m_elapsedTime; //elapsed time since the last emission
    unsigned int m_speed; //base speed of the particles
    unsigned int m_speedOffset; //offset for random speed variation
    unsigned int m_minAngle; //min angle of particle emission
    unsigned int m_maxAngle; //max angle of particle emission

    std::vector<Particle> particles; //collection of particles
};
