#include "Particle.hpp"
#include <iostream>

Particle::Particle(float lifespan, Position position, Position velocity)
    : lifespan(lifespan), position(position), velocity(velocity), timeInLife(0.0f) {}

void Particle::update(float deltaTime) {
    timeInLife += deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

bool Particle::isAlive() const {
    std::cout << "lifespan" << lifespan << std::endl;
    return timeInLife < lifespan;
}
