#pragma once

#include <cstdint>
#include <vector>

#include "Component.h"
#include "Particle.h"
#include "Transform.h"

class Sprite;

namespace crepe {

class ParticleEmitter : public Component {
public:
	struct ParticleBoundary{
		//! boundary width (midpoint is emitter location)
		double boundary_width = 0.0;
		//! boundary height (midpoint is emitter location)
		double boundary_height = 0.0;
		//! boundary offset from particle emitter location
		Vector2 boundary_offset;
		//! reset on exit or stop velocity and set max postion
		bool reset_on_exit = false;
	};

	struct ParticleEmitterData{
		//! position of the emitter
		Vector2 position;
		//! maximum number of particles
		uint32_t max_particles = 0;
		//! rate of particle emission per update (Lowest value = 0.001 any lower is ignored)
		double emission_rate = 0;
		//! min speed of the particles
		double min_speed = 0;
		//! min speed of the particles
		double max_speed = 0;
		//! min angle of particle emission
		double min_angle = 0;
		//! max angle of particle emission
		double max_angle = 0;
		//! begin Lifespan of particle (only visual)
		double begin_lifespan = 0.0;
		//! end Lifespan of particle
		double end_lifespan = 0.0;
		//! force over time (physics)
		Vector2 force_over_time;
		//! particle boundary
		ParticleBoundary boundary;
		//! collection of particles
		std::vector<Particle> particles;
		//! sprite reference
		const Sprite* sprite;
	};	
public:
	ParticleEmitter(uint32_t game_object_id, const ParticleEmitterData& data);
	~ParticleEmitter();
public:
	ParticleEmitterData data;
};

} // namespace crepe
