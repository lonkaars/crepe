#include "Particle.hpp"


Particle::Particle(float lifespan, Position position, Position velocity)
    : lifespan(lifespan), position(position), velocity(velocity), timeInLife(0.0f) {}

void Particle::update(float deltaTime) {
    timeInLife += deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

bool Particle::isAlive() const {
    return timeInLife < lifespan;
}
