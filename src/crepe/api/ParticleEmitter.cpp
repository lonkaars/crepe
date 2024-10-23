#include <ctime>
#include <iostream>

#include "Particle.h"
#include "ParticleEmitter.h"

using namespace crepe;

ParticleEmitter::ParticleEmitter(uint32_t game_object_id,
								 uint32_t max_particles, uint32_t emission_rate,
								 uint32_t speed, uint32_t speed_offset,
								 uint32_t angle, uint32_t angleOffset,
								 float begin_lifespan, float end_lifespan)
	: Component(game_object_id), max_particles(max_particles),
	  emission_rate(emission_rate), speed(speed), speed_offset(speed_offset),
	  position{0, 0}, begin_lifespan(begin_lifespan),
	  end_lifespan(end_lifespan) {
	std::srand(
		static_cast<uint32_t>(std::time(nullptr))); // initialize random seed
	std::cout << "Create emitter" << std::endl;
	min_angle = (360 + angle - (angleOffset % 360)) % 360; // calculate minAngle
	max_angle = (360 + angle + (angleOffset % 360)) % 360; // calculate maxAngle
	position.x = 400;
	position.y = 400;
	for (size_t i = 0; i < max_particles; i++) {
		this->particles.emplace_back();
	}
}

ParticleEmitter::~ParticleEmitter() {
	std::vector<Particle>::iterator it = this->particles.begin();
	while (it != this->particles.end()) {
		it = this->particles.erase(it);
	}
}
