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
        m_elapsedTime = deltaTime;

        //spawn new particles if enough time passed and the max is not achieved
        while (m_elapsedTime >= (1.0f / emitter.m_emissionRate) && emitter.particles.size() < emitter.m_maxParticles) {
            m_elapsedTime -= (1.0f / emitter.m_emissionRate);
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
    std::cout << "new emitter:" << std::endl;
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
    
    std::cout << "randomAngle:" << randomAngle << std::endl;
    float angleInRadians = randomAngle * (M_PI / 180.0f);
    float randomSpeedOffset = (static_cast<float>(std::rand()) / RAND_MAX) * (2 * emitter.m_speedOffset) - emitter.m_speedOffset;
    float velocityX = (emitter.m_speed + randomSpeedOffset) * std::cos(angleInRadians);
    float velocityY = (emitter.m_speed + randomSpeedOffset) * std::sin(angleInRadians);
    std::cout << "velocityX:" << velocityX << std::endl;
    std::cout << "velocityY:" << velocityY << std::endl;
    Particle::Position initialVelocity = {
        velocityX,
        velocityY
    };
    std::cout << "initialVelocityX:" << initialVelocity.x << std::endl;
    std::cout << "initialVelocityY:" << initialVelocity.y << std::endl;
    emitter.particles.emplace_back(2.0f, initialPosition, initialVelocity);
}
