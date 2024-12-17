#pragma once

#include <cstdint>

#include "System.h"

namespace crepe {

class ParticleEmitter;
class Transform;

/**
 * \brief ParticleSystem class responsible for managing particle emission, updates, and bounds
 * checking.
 */
class ParticleSystem : public System {
public:
	using System::System;
	/**
	 * \brief Updates all particle emitters by emitting particles, updating particle states, and
	 * checking bounds.
	 */
	void fixed_update() override;

private:
	/**
	 * \brief Emits a particle from the specified emitter based on its emission properties.
	 *
	 * \param emitter Reference to the ParticleEmitter.
	 * \param transform Const reference to the Transform component associated with the emitter.
	 */
	void emit_particle(ParticleEmitter & emitter, const Transform & transform);

	/**
	 * \brief Checks whether particles are within the emitter’s boundary, resets or stops
	 * particles if they exit.
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
	float generate_random_angle(float min_angle, float max_angle) const;

	/**
	 * \brief Generates a random speed for particle emission within the specified range.
	 *
	 * \param min_speed Minimum emission speed.
	 * \param max_speed Maximum emission speed.
	 * \return Random speed.
	 */
	float generate_random_speed(float min_speed, float max_speed) const;
};

} // namespace crepe
