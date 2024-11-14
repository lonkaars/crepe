#pragma once

#include <vector>

#include "Component.h"
#include "Particle.h"
#include "Vector2.h"

namespace crepe {

class Sprite;

/**
 * \brief Data holder for particle emission parameters.
 *
 * The ParticleEmitter class stores configuration data for particle properties,
 * defining the characteristics and boundaries of particle emissions.
 */
class ParticleEmitter : public Component {
public:
	/**
	 * \brief Defines the boundary within which particles are constrained.
	 *
	 * This structure specifies the boundary's size and offset, as well as the
	 * behavior of particles upon reaching the boundary limits.
	 */
	struct Boundary {
		//! boundary width (midpoint is emitter location)
		double width = 0.0;
		//! boundary height (midpoint is emitter location)
		double height = 0.0;
		//! boundary offset from particle emitter location
		Vector2 offset;
		//! reset on exit or stop velocity and set max postion
		bool reset_on_exit = false;
	};

	/**
	 * \brief Holds parameters that control particle emission.
	 *
	 * Contains settings for the emitter’s position, particle speed, angle, lifespan,
	 * boundary, and the sprite used for rendering particles.
	 */
	struct Data {
		//! position of the emitter
		Vector2 position;
		//! maximum number of particles
		const unsigned int max_particles = 0;
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
		Boundary boundary;
		//! collection of particles
		std::vector<Particle> particles;
		//! sprite reference
		const Sprite & sprite;
	};

public:
	/**
	 * \param game_object_id  Identifier for the game object using this emitter.
	 * \param data            Configuration data defining particle properties.
	 */
	ParticleEmitter(game_object_id_t game_object_id, const Data & data);

public:
	//! Configuration data for particle emission settings.
	Data data;
};

} // namespace crepe
