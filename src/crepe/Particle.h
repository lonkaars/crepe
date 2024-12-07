#pragma once

#include <cstdint>

#include "types.h"

namespace crepe {

/**
 * \brief Represents a particle in the particle emitter.
 *
 * This class stores information about a single particle, including its position, velocity,
 * lifespan, and other properties. Particles can be updated over time to simulate movement and
 * can also be reset or stopped.
 */
class Particle {
	// TODO: add friend particleSsytem and rendersystem. Unit test will fail.

public:
	//! Position of the particle in 2D space.
	vec2 position;
	//! Velocity vector indicating the speed and direction of the particle.
	vec2 velocity;
	//! Accumulated force affecting the particle over time.
	vec2 force_over_time;
	//! Total lifespan of the particle in milliseconds.
	float lifespan;
	//! Active state of the particle; true if it is in use, false otherwise.
	bool active = false;
	//! The time the particle has been alive, in milliseconds.
	float time_in_life = 0;
	//! The angle at which the particle is oriented or moving.
	float angle = 0;

	/**
	 * \brief Resets the particle with new properties.
	 *
	 * This method initializes the particle with a specific lifespan, position, velocity, and
	 * angle, marking it as active and resetting its life counter.
	 *
	 * \param lifespan  The lifespan of the particle in amount of updates.
	 * \param position  The starting position of the particle.
	 * \param velocity  The initial velocity of the particle.
	 * \param angle     The angle of the particle's trajectory or orientation.
	 */
	void reset(unsigned int lifespan, const vec2 & position, const vec2 & velocity, float angle);
	/**
	 * \brief Updates the particle's state.
	 *
	 * Advances the particle's position based on its velocity and applies accumulated forces.
	 * Deactivates the particle if its lifespan has expired.
	 * \param dt The amount of fixed delta time that has passed.
	 */
	void update(double dt);
	/**
	 * \brief Stops the particle's movement.
	 *
	 * Sets the particle's velocity to zero, effectively halting any further
	 * movement.
	 */
	void stop_movement();
};

} // namespace crepe
