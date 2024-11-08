#pragma once

#include "System.h"

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
	/**
	 * \brief Retrieves the singleton instance of the AnimatorSystem.
	 *
	 * \return A reference to the single instance of the AnimatorSystem.
	 *
	 * This method ensures that there is only one instance of the AnimatorSystem, following the
	 * singleton design pattern. It can be used to access the system globally.
	 */
	static AnimatorSystem & get_instance();

	/**
	 * \brief Updates the Animator components.
	 *
	 * This method is called periodically (likely every frame) to update the state of all
	 * Animator components, moving the animations forward and managing their behavior (e.g., looping).
	 */
	void update() override;

private:
	/**
	 * \brief Private constructor for the AnimatorSystem.
	 *
	 * The constructor is private to enforce the singleton pattern, ensuring that only
	 * one instance of this system can exist.
	 */
	AnimatorSystem();

	/**
	 * \brief Private destructor for the AnimatorSystem.
	 *
	 * The destructor cleans up any resources used by the AnimatorSystem. It is private
	 * to maintain the singleton pattern and prevent direct deletion.
	 */
	~AnimatorSystem();
};

} // namespace crepe
