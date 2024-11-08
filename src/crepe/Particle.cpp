#include "Particle.h"

#include "api/Transform.h"

using namespace crepe;

void Particle::reset(uint32_t lifespan, Vector2 position, Vector2 velocity, double angle) {
	this->time_in_life = 0;
	this->lifespan = lifespan;
	this->position = position;
	this->velocity = velocity;
	this->active = true;
	this->angle = angle;
}

void Particle::update() {
	time_in_life++;
	if (time_in_life >= lifespan) 
	{
		this->active = false;
		return;
	}	
	velocity += force_over_time;
	position += velocity;
}

void Particle::stop_movement() {
	this->velocity = {0,0};
}
