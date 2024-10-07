#include "ParticleSystem.hpp"
#include <cmath>
// #include <cstdlib>
#include <ctime>
#include <iostream>  // include iostream for std::cout
#include "ParticleEmitter.hpp"
#include "Particle.hpp"

ParticleSystem::ParticleSystem() : m_elapsedTime(0.0f) {}  // Initialize m_elapsedTime to 0

void ParticleSystem::update(float deltaTime, std::vector<ParticleEmitter>& emitters) {
    // std::cout << "ParticleSystem update" << std::endl;
    for (ParticleEmitter& emitter : emitters) {
        float updateAmount = 1/static_cast<float>(emitter.m_emissionRate);
        for (float i = 0; i < deltaTime; i += updateAmount)
        {
            emitParticle(emitter);
        }
        //  std::cout << "after emit" << std::endl;
        
        //update/move particles afterwards delete if not alive.
        for (size_t j = 0; j <  emitter.particles.size(); j++)
        {
            // std::cout << "update" << std::endl;
            if(emitter.particles[j].active)
            {
                emitter.particles[j].update(deltaTime);
            }
        }     


    }
}

void ParticleSystem::emitParticle(ParticleEmitter& emitter) {
    // std::cout << "new emitter:" << std::endl;
    Position initialPosition = { emitter.m_position.x, emitter.m_position.y };
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
    Position initialVelocity = {
        velocityX,
        velocityY
    };
    // std::cout << "emitter.m_endLifespan:" << emitter.m_endLifespan << std::endl;
    for (size_t i = 0; i < emitter.particles.size(); i++)
    {
        if(!emitter.particles[i].active)
        {
            // std::cout << "active " << emitter.particles[i].active << std::endl;
            // std::cout << "lifespan " << emitter.particles[i].lifespan << std::endl;
            // std::cout << "timeInLife " << emitter.particles[i].timeInLife << std::endl;
            // std::cout << "emitter.m_endLifespan" << emitter.m_endLifespan << std::endl;
            // std::cout << "initialPositionx" << initialPosition.x << std::endl;
            // std::cout << "initialPositiony" << initialPosition.y << std::endl;
            // std::cout << "initialVelocityx" << initialVelocity.x << std::endl;
            // std::cout << "initialVelocityy" << initialVelocity.y << std::endl;
            emitter.particles[i].reset(emitter.m_endLifespan, initialPosition, initialVelocity);
            break;
        }
    }
    
    //emitter.particles.emplace_back(emitter.m_endLifespan, initialPosition, initialVelocity);
}
