#pragma once

#include <cstdint>

#include "api/Vector2.h"

namespace crepe {

/**
 * \brief Represents a particle in the particle emitter.
 *
 * This class stores information about a single particle, including its position,
 * velocity, lifespan, and other properties. Particles can be updated over time
 * to simulate movement and can also be reset or stopped.
 */
class Particle {
	// TODO: add friend particleSsytem and rendersystem. Unit test will fail.

public:
	//! Position of the particle in 2D space.
	Vector2 position;
	//! Velocity vector indicating the speed and direction of the particle.
	Vector2 velocity;
	//! Accumulated force affecting the particle over time.
	Vector2 force_over_time;
	//! Total lifespan of the particle in milliseconds.
	uint32_t lifespan;
	//! Active state of the particle; true if it is in use, false otherwise.
	bool active = false;
	//! The time the particle has been alive, in milliseconds.
	uint32_t time_in_life = 0;
	//! The angle at which the particle is oriented or moving.
	double angle = 0;

	/**
	 * \brief Resets the particle with new properties.
	 *
	 * This method initializes the particle with a specific lifespan, position,
	 * velocity, and angle, marking it as active and resetting its life counter.
	 *
	 * \param lifespan  The lifespan of the particle in amount of updates.
	 * \param position  The starting position of the particle.
	 * \param velocity  The initial velocity of the particle.
	 * \param angle     The angle of the particle's trajectory or orientation.
	 */
	void reset(uint32_t lifespan, const Vector2 & position,
			   const Vector2 & velocity, double angle);
	/**
	 * \brief Updates the particle's state.
	 *
	 * Advances the particle's position based on its velocity and applies accumulated forces. 
	 * Deactivates the particle if its lifespan has expired.
	 */
	void update();
	/**
	 * \brief Stops the particle's movement.
	 *
	 * Sets the particle's velocity to zero, effectively halting any further
	 * movement.
	 */
	void stop_movement();
};

} // namespace crepe
