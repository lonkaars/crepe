#include "ParticleEmitter.h"
#include "Particle.h"
#include <ctime>
#include <iostream>

using namespace crepe;

ParticleEmitter::ParticleEmitter(uint32_t gameObjectId, uint32_t max_particles,
								 uint32_t emission_rate, uint32_t speed,
								 uint32_t speed_offset, uint32_t angle,
								 uint32_t angleOffset, float m_begin_lifespan,
								 float m_end_lifespan)
	: Component(gameObjectId), m_max_particles(max_particles),
	  m_emission_rate(emission_rate), m_speed(speed), m_speed_offset(speed_offset),
	  m_position{0, 0}, m_begin_lifespan(m_begin_lifespan),
	  m_end_lifespan(m_end_lifespan) {
	std::srand(
		static_cast<uint32_t>(std::time(nullptr))); // initialize random seed
	std::cout << "Create emitter" << std::endl;
	m_min_angle
		= (360 + angle - (angleOffset % 360)) % 360; // calculate minAngle
	m_max_angle
		= (360 + angle + (angleOffset % 360)) % 360; // calculate maxAngle
	m_position.x = 400;
	m_position.y = 400;
	for (size_t i = 0; i < m_max_particles; i++) {
		this->particles.emplace_back();
	}
}

ParticleEmitter::~ParticleEmitter() {
	std::vector<Particle>::iterator it = this->particles.begin();
	while (it != this->particles.end()) {
		it = this->particles.erase(it);
	}
}
