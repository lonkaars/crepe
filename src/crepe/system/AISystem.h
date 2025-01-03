#pragma once

#include "api/AI.h"
#include "api/Rigidbody.h"

#include "System.h"
#include "api/Transform.h"
#include "types.h"

namespace crepe {

/**
 * \brief The AISystem is used to control the movement of entities using AI.
 *
 * The AISystem is used to control the movement of entities using AI. The AISystem can be used to
 * implement different behaviors such as seeking, fleeing, arriving, and path following.
 */
class AISystem : public System {
public:
	using System::System;

	//! Update the AI system
	void fixed_update() override;

private:
	/**
	 * \brief Calculate the total force to apply to the entity
	 *
	 * \param ai The AI component
	 * \param rigidbody The Rigidbody component
	 */
	vec2 calculate(AI & ai, const Rigidbody & rigidbody);
	/**
	 * \brief Accumulate the force to apply to the entity
	 *
	 * \param ai The AI component
	 * \param running_total The running total of the force
	 * \param force_to_add The force to add
	 * \return true if the force was added, false otherwise
	 */
	bool accumulate_force(const AI & ai, vec2 & running_total, vec2 & force_to_add);

	/**
	 * \brief Calculate the seek force
	 *
	 * \param ai The AI component
	 * \param rigidbody The Rigidbody component
	 * \param transform The Transform component
	 * \return The seek force
	 */
	vec2 seek(const AI & ai, const Rigidbody & rigidbody, const Transform & transform) const;
	/**
	 * \brief Calculate the flee force
	 *
	 * \param ai The AI component
	 * \param rigidbody The Rigidbody component
	 * \param transform The Transform component
	 * \return The flee force
	 */
	vec2 flee(const AI & ai, const Rigidbody & rigidbody, const Transform & transform) const;
	/**
	 * \brief Calculate the arrive force
	 *
	 * \param ai The AI component
	 * \param rigidbody The Rigidbody component
	 * \param transform The Transform component
	 * \return The arrive force
	 */
	vec2 arrive(const AI & ai, const Rigidbody & rigidbody, const Transform & transform) const;
	/**
	 * \brief Calculate the path follow force
	 *
	 * \param ai The AI component
	 * \param rigidbody The Rigidbody component
	 * \param transform The Transform component
	 * \return The path follow force
	 */
	vec2 path_follow(AI & ai, const Rigidbody & rigidbody, const Transform & transform);
};

} // namespace crepe
