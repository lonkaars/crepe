#pragma once

#include <cstdint>

#include "System.h"

#include "System.h"

namespace crepe {

class ParticleEmitter;
class Transform;

/**
 	* \brief ParticleSystem class responsible for managing particle emission, updates, and bounds checking.
 	*/
class ParticleSystem : public System{
public:
	using System::System;
	/**
	 * \brief Updates all particle emitters by emitting particles, updating particle states, and checking bounds.
	 */
	void update() override;

private:
	/**
	 * \brief Emits a particle from the specified emitter based on its emission properties.
	 * 
	 * \param emitter Reference to the ParticleEmitter.
	 * \param transform Const reference to the Transform component associated with the emitter.
	 */
	void emit_particle(ParticleEmitter & emitter, const Transform & transform);

	/**
	 * \brief Calculates the number of times particles should be emitted based on emission rate and update count.
	 * 
	 * \param count Current update count.
	 * \param emission Emission rate.
	 * \return The number of particles to emit.
	 */
	int calculate_update(int count, double emission) const;

	/**
	 * \brief Checks whether particles are within the emitter’s boundary, resets or stops particles if they exit.
	 * 
	 * \param emitter Reference to the ParticleEmitter.
	 * \param transform Const reference to the Transform component associated with the emitter.
	 */
	void check_bounds(ParticleEmitter & emitter, const Transform & transform);

	/**
	 * \brief Generates a random angle for particle emission within the specified range.
	 * 
	 * \param min_angle Minimum emission angle in degrees.
	 * \param max_angle Maximum emission angle in degrees.
	 * \return Random angle in degrees.
	 */
	double generate_random_angle(double min_angle, double max_angle) const;

	/**
	 * \brief Generates a random speed for particle emission within the specified range.
	 * 
	 * \param min_speed Minimum emission speed.
	 * \param max_speed Maximum emission speed.
	 * \return Random speed.
	 */
	double generate_random_speed(double min_speed, double max_speed) const;

private:
	//! Counter to count updates to determine how many times emit_particle is called.
	uint32_t update_count = 0;
	//! Determines the lowest amount of emission rate (1000 = 0.001 = 1 particle per 1000 updates).
	static constexpr unsigned int MAX_UPDATE_COUNT = 100;
};

} // namespace crepe
