#include "ParticleEmitter.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>  // include iostream for std::cout

ParticleEmitter::ParticleEmitter(unsigned int maxParticles, unsigned int emissionRate, unsigned int speed, unsigned int speedOffset, unsigned int angle, unsigned int angleOffset)
    : m_maxParticles(maxParticles), m_emissionRate(emissionRate), m_elapsedTime(0.0f), m_speed(speed), m_speedOffset(speedOffset), m_position{0, 0} {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // initialize random seed

    m_minAngle = (360 + angle - (angleOffset % 360)) % 360; // calculate minAngle
    m_maxAngle = (360 + angle + (angleOffset % 360)) % 360; // calculate maxAngle

    std::cout << "Initialized ParticleEmitter with:" << std::endl;
    std::cout << "Min Angle: " << m_minAngle << " Max Angle: " << m_maxAngle << std::endl;
}

void ParticleEmitter::update(float deltaTime) { // keep deltaTime as float
    m_elapsedTime += deltaTime;

    while (m_elapsedTime >= (1.0f / m_emissionRate) && particles.size() < m_maxParticles) {
        m_elapsedTime -= (1.0f / m_emissionRate);
        emitParticle();
    }

    std::vector<Particle>::iterator it = particles.begin();
    while (it != particles.end()) {
        it->update(deltaTime); // update particle
        if (!it->isAlive()) {
            it = particles.erase(it); // remove dead particle
        } else {
            ++it; // move to next particle
        }
    }
}

void ParticleEmitter::emitParticle() {
    Particle::Position initialPosition = { m_position.x, m_position.y }; // starting position of the particle

    // generate a random angle within the range [minAngle, maxAngle]
    float randomAngle = m_minAngle + (std::rand() % (static_cast<int>(m_maxAngle - m_minAngle + 1))); // random angle within the specified range

    // convert angle to radians for velocity calculation
    float angleInRadians = randomAngle * (M_PI / 180.0f);

    // calculate velocity components based on the final angle
    float randomSpeedOffset = (static_cast<float>(std::rand()) / RAND_MAX) * (2 * m_speedOffset) - m_speedOffset; // random speed offset
    float velocityX = (m_speed + randomSpeedOffset) * std::cos(angleInRadians); // x component of velocity
    float velocityY = (m_speed + randomSpeedOffset) * std::sin(angleInRadians); // y component of velocity

    Particle::Position initialVelocity = {
        static_cast<int>(velocityX), // set x velocity
        static_cast<int>(velocityY)  // set y velocity
    };

    std::cout << "Emitting particle with:" << std::endl;
    std::cout << "Random Angle: " << randomAngle << " (Radians: " << angleInRadians << ")" << std::endl;
    std::cout << "Velocity X: " << velocityX << " Velocity Y: " << velocityY << std::endl;

    particles.emplace_back(2.0f, initialPosition, initialVelocity); // create and store the new particle
}

const std::vector<Particle>& ParticleEmitter::getParticles() const {
    return particles; // return the collection of particles
}

void ParticleEmitter::setPosition(int x, int y) {
    m_position.x = x; // set x position of the emitter
    m_position.y = y; // set y position of the emitter
}
