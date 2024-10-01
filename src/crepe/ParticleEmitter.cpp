#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter(int maxParticles, float emissionRate)
    : maxParticles(maxParticles), emissionRate(emissionRate), elapsedTime(0.0f) {
    position = { 0, 0 };  
    std::srand(static_cast<unsigned int>(std::time(nullptr))); /
}

void ParticleEmitter::update(float deltaTime) {
    elapsedTime += deltaTime;

    while (elapsedTime >= (1.0f / emissionRate) && particles.size() < maxParticles) {
        elapsedTime -= (1.0f / emissionRate);
        emitParticle();
    }

    for (auto it = particles.begin(); it != particles.end();) {
        it->update(deltaTime);
        if (!it->isAlive()) {
            it = particles.erase(it); 
        } else {
            ++it;
        }
    }
}

void ParticleEmitter::emitParticle() {
    Particle::Position initialPosition = { position.x, position.y };
    Particle::Position initialVelocity = {
        static_cast<int>(randFloat(-50.0f, 50.0f, 10.0f, 100.0f)), 
        static_cast<int>(randFloat(-50.0f, 50.0f, 10.0f, 100.0f))
    };
    particles.emplace_back(2.0f, initialPosition, initialVelocity); 
}

float ParticleEmitter::randFloat(float minangle, float maxangle, float minVel, float maxVel) {
    float angle = static_cast<float>(rand()) / RAND_MAX * (maxangle - minangle) + minangle;
    float velocity = static_cast<float>(rand()) / RAND_MAX * (maxVel - minVel) + minVel;
    return velocity * std::cos(angle); 
}
