#include "Particle.h"

using namespace crepe;

void Particle::reset(
	unsigned int lifespan, const vec2 & position, const vec2 & velocity, float angle
) {
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

void Particle::update(double dt) {
	// Deactivate particle if it has exceeded its lifespan
	time_in_life += dt;
	if (time_in_life >= lifespan) {
		this->active = false;
		return;
	}

	// Update velocity based on accumulated force and update position
	this->velocity += force_over_time * dt;
	this->position += velocity * dt;
}

void Particle::stop_movement() {
	// Reset velocity to halt movement
	this->velocity = {0, 0};
}
