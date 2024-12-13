#pragma once

#include <cmath>
#include <vector>

#include "system/ParticleSystem.h"
#include "system/RenderSystem.h"

#include "Component.h"
#include "Particle.h"
#include "types.h"

namespace crepe {

class Sprite;

/**
 * \brief Data holder for particle emission parameters.
 *
 * The ParticleEmitter class stores configuration data for particle properties, defining the
 * characteristics and boundaries of particle emissions.
 */
class ParticleEmitter : public Component {
public:
	/**
	 * \brief Defines the boundary within which particles are constrained.
	 *
	 * This structure specifies the boundary's size and offset, as well as the behavior of
	 * particles upon reaching the boundary limits.
	 */
	struct Boundary {
		//! boundary width (midpoint is emitter location)
		float width = INFINITY;
		//! boundary height (midpoint is emitter location)
		float height = INFINITY;
		//! boundary offset from particle emitter location
		vec2 offset;
		//! reset on exit or stop velocity and set max postion
		bool reset_on_exit = false;
	};

	//! sprite reference of displayed sprite
	const Sprite & sprite;

	/**
	 * \brief Holds parameters that control particle emission.
	 *
	 * Contains settings for the emitter’s position, particle speed, angle, lifespan, boundary,
	 * and the sprite used for rendering particles.
	 */
	struct Data {
		//! position of the emitter
		vec2 position;
		//! maximum number of particles
		const unsigned int max_particles = 256;
		//! rate of particle emission per second
		float emission_rate = 50;
		//! min speed of the particles
		float min_speed = 100;
		//! min speed of the particles
		float max_speed = 100;
		//! min angle of particle emission
		float min_angle = 0;
		//! max angle of particle emission
		float max_angle = 0;
		//! begin Lifespan of particle in seconds (only visual)
		float begin_lifespan = 0.0;
		//! end Lifespan of particle in seconds
		float end_lifespan = 10.0;
		//! force over time (physics)
		vec2 force_over_time;
		//! particle boundary
		Boundary boundary;
	};

public:
	/**
	 * \param game_object_id  Identifier for the game object using this emitter.
	 * \param data            Configuration data defining particle properties.
	 */
	ParticleEmitter(game_object_id_t game_object_id, const Sprite & sprite, const Data & data);

public:
	//! Configuration data for particle emission settings.
	Data data;

private:
	//! Only ParticleSystem can move and read particles
	friend ParticleSystem;
	//! Only RenderSystem can read particles
	friend RenderSystem;
	//! Saves time left over from last update event.
	float spawn_accumulator = 0;
	//! collection of particles
	std::vector<Particle> particles;
};

} // namespace crepe
