#include "Particle.h"

#include "api/Transform.h"

using namespace crepe;

void Particle::reset(uint32_t lifespan, Vector2 position, Vector2 velocity, double angle) {
	// Initialize the particle state
	this->time_in_life = 0;
	this->lifespan = lifespan;
	this->position = position;
	this->velocity = velocity;
	this->angle = angle;
	this->active = true;
	// Reset force accumulation
	this->force_over_time = {0, 0};
}

void Particle::update() {
	// Deactivate particle if it has exceeded its lifespan
	if (++time_in_life >= lifespan) {
		this->active = false;
		return;
	}

	// Update velocity based on accumulated force and update position
	this->velocity += force_over_time;
	this->position += velocity;
}

void Particle::stop_movement() {
	// Reset velocity to halt movement
	this->velocity = {0, 0};
}
