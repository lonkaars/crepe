#include "Particle.h"

using namespace crepe;

Particle::Particle() { this->active = false; }

void Particle::reset(float lifespan, Position position, Position velocity) {
	this->time_in_life = 0;
	this->lifespan = lifespan;
	this->position = position;
	this->velocity = velocity;
	this->active = true;
}

void Particle::update(float deltaTime) {
	time_in_life += deltaTime;
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	if (time_in_life >= lifespan) this->active = false;
}
