#include "Particle.hpp"
#include <iostream>

Particle::Particle()
{
    this->active = false;
}

void Particle::reset(float lifespan, Position position, Position velocity) {
    this->timeInLife = 0;
    this->lifespan = lifespan;
    this->position = position;
    this->velocity = velocity;
    this->active = true;
}

void Particle::update(float deltaTime) {
    timeInLife += deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    if(timeInLife >= lifespan)this->active = false;
}

