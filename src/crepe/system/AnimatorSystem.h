#pragma once

#include "System.h"
#include "api/LoopTimer.h"

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
	 * This method is called to update the state of all
	 * Animator components, moving the animations forward and managing their behavior (e.g.,
	 * looping).
	 */
	void update() override;

private:
	LoopTimer & timer = LoopTimer::get_instance();
};

} // namespace crepe
