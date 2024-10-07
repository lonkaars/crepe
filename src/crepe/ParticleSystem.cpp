#include "ParticleSystem.hpp"
#include <cmath>
// #include <cstdlib>
#include <ctime>
#include <iostream>  // include iostream for std::cout
#include "ParticleEmitter.hpp"
#include "Particle.hpp"

ParticleSystem::ParticleSystem() : m_elapsedTime(0.0f) {}  // Initialize m_elapsedTime to 0

void ParticleSystem::update(float deltaTime, std::vector<ParticleEmitter>& emitters) {
    for (ParticleEmitter& emitter : emitters) {
        float updateAmount = 1/static_cast<float>(emitter.m_emissionRate);
        for (float i = 0; i < deltaTime; i += updateAmount)
        {
            emitParticle(emitter);
        }
        
        //update/move particles afterwards delete if not alive.
        std::vector<Particle>::iterator it = emitter.particles.begin();
        while (it != emitter.particles.end()) {
            it->update(deltaTime);
            if (!it->isAlive()) {
                it = emitter.particles.erase(it);
            } else {
                ++it;
            }
        }

    }
}

void ParticleSystem::emitParticle(ParticleEmitter& emitter) {
    // std::cout << "new emitter:" << std::endl;
    Particle::Position initialPosition = { emitter.m_position.x, emitter.m_position.y };
    float randomAngle = 0.0f;
    //check if value is overthe 360 degrees
    if(emitter.m_maxAngle < emitter.m_minAngle)
    {
        randomAngle = ((emitter.m_minAngle + (std::rand() % (static_cast<int>(emitter.m_maxAngle + 360 - emitter.m_minAngle + 1))))%360);
    }
    else
    {
        randomAngle = emitter.m_minAngle + (std::rand() % (static_cast<int>(emitter.m_maxAngle - emitter.m_minAngle + 1)));
    }
    

    float angleInRadians = randomAngle * (M_PI / 180.0f);
    float randomSpeedOffset = (static_cast<float>(std::rand()) / RAND_MAX) * (2 * emitter.m_speedOffset) - emitter.m_speedOffset;
    float velocityX = (emitter.m_speed + randomSpeedOffset) * std::cos(angleInRadians);
    float velocityY = (emitter.m_speed + randomSpeedOffset) * std::sin(angleInRadians);
    Particle::Position initialVelocity = {
        velocityX,
        velocityY
    };
    // std::cout << "emitter.m_endLifespan:" << emitter.m_endLifespan << std::endl;

    emitter.particles.emplace_back(emitter.m_endLifespan, initialPosition, initialVelocity);
}
