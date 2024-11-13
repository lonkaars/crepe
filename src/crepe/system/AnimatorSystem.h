#pragma once

#include "System.h"

//TODO:
// control if flip works with animation system

namespace crepe {

/**
 * \brief The AnimatorSystem is responsible for managing and updating all Animator components.
 *
 * This system is responsible for controlling the behavior of the animations for all entities
 * that have the Animator component attached. It updates the animations by controlling their
 * frame changes, looping behavior, and overall animation state.
 */
class AnimatorSystem : public System {

public:
	using System::System;
	/**
	 * \brief Updates the Animator components.
	 *
	 * This method is called periodically (likely every frame) to update the state of all
	 * Animator components, moving the animations forward and managing their behavior (e.g., looping).
	 */
	void update() override;
	// FIXME: never say "likely" in the documentation lmao
};

} // namespace crepe
