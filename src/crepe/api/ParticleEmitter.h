#pragma once

#include <cstdint>
#include <vector>

#include "Component.h"
#include "Particle.h"

namespace crepe {

class ParticleEmitter : public Component {
public:
	ParticleEmitter(game_object_id_t id, uint32_t max_particles,
					uint32_t emission_rate, uint32_t speed,
					uint32_t speed_offset, uint32_t angle, uint32_t angleOffset,
					float begin_lifespan, float end_lifespan);
	~ParticleEmitter();

	//! position of the emitter
	Position position;
	//! maximum number of particles
	uint32_t max_particles;
	//! rate of particle emission
	uint32_t emission_rate;
	//! base speed of the particles
	uint32_t speed;
	//! offset for random speed variation
	uint32_t speed_offset;
	//! min angle of particle emission
	uint32_t min_angle;
	//! max angle of particle emission
	uint32_t max_angle;
	//! begin Lifespan of particle (only visual)
	float begin_lifespan;
	//! begin Lifespan of particle
	float end_lifespan;

	//! collection of particles
	std::vector<Particle> particles;
};

} // namespace crepe
