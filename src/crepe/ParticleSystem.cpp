#include "ParticleSystem.h"
#include <cmath>
// #include <cstdlib>
#include <ctime>
#include <iostream>  // include iostream for std::cout
#include "ParticleEmitter.h"
#include "Particle.h"
#include "ComponentManager.h"

using namespace crepe;

ParticleSystem::ParticleSystem() : m_elapsedTime(0.0f) {}  // Initialize m_elapsedTime to 0

void ParticleSystem::update(float deltaTime, std::vector<std::reference_wrapper<ParticleEmitter>>& emitters) {
    for (ParticleEmitter& emitter : emitters) {
        float updateAmount = 1/static_cast<float>(emitter.m_emissionRate);
        for (float i = 0; i < deltaTime; i += updateAmount)
        {
            emitParticle(emitter);
        }
        for (size_t j = 0; j <  emitter.particles.size(); j++)
        {
            if(emitter.particles[j].active)
            {
                emitter.particles[j].update(deltaTime);
            }
        }     
    }
}

void ParticleSystem::emitParticle(ParticleEmitter& emitter) {
    Position initialPosition = { emitter.m_position.x, emitter.m_position.y};
    float randomAngle = 0.0f;
    if(emitter.m_maxAngle < emitter.m_minAngle)
    {
        randomAngle = ((emitter.m_minAngle + (std::rand() % (static_cast<uint32_t>(emitter.m_maxAngle + 360 - emitter.m_minAngle + 1))))%360);
    }
    else
    {
        randomAngle = emitter.m_minAngle + (std::rand() % (static_cast<uint32_t>(emitter.m_maxAngle - emitter.m_minAngle + 1)));
    }
    float angleInRadians = randomAngle * (M_PI / 180.0f);
    float randomSpeedOffset = (static_cast<float>(std::rand()) / RAND_MAX) * (2 * emitter.m_speedOffset) - emitter.m_speedOffset;
    float velocityX = (emitter.m_speed + randomSpeedOffset) * std::cos(angleInRadians);
    float velocityY = (emitter.m_speed + randomSpeedOffset) * std::sin(angleInRadians);
    Position initialVelocity = {
        velocityX,
        velocityY
    };
    for (size_t i = 0; i < emitter.particles.size(); i++)
    {
        if(!emitter.particles[i].active)
        {
            emitter.particles[i].reset(emitter.m_endLifespan, initialPosition, initialVelocity);
            break;
        }
    }
}
