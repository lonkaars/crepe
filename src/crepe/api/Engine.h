#pragma once

#include "../facade/SDLContext.h"
#include "../manager/ComponentManager.h"
#include "../manager/EventManager.h"
#include "../manager/LoopTimerManager.h"
#include "../manager/ReplayManager.h"
#include "../manager/ResourceManager.h"
#include "../manager/SaveManager.h"
#include "../manager/SceneManager.h"
#include "../manager/SystemManager.h"

namespace crepe {

/**
 * \brief Main game entrypoint
 *
 * This class is responsible for managing the game loop, including initialization and updating.
 */
class Engine {
public:
	/**
	 * \brief Engine entrypoint
	 *
	 * This function is called by the game programmer after registering all scenes
	 *
	 * \returns process exit code
	 */
	int main() noexcept;

	//! \copydoc SceneManager::add_scene
	template <typename T>
	void add_scene();

private:
	/**
	 * \brief Setup function for one-time initialization.
	 *
	 * This function initializes necessary components for the game.
	 */
	void setup();
	/**
	 * \brief Main game loop function.
	 *
	 * This function runs the main loop, handling game updates and rendering.
	 */
	void loop();

	//! Game loop condition
	bool game_running = true;

private:
	//! Global context
	Mediator mediator;

	//! SystemManager
	SystemManager system_manager {mediator};

	//! SDLContext instance
	SDLContext sdl_context {mediator};

	//! Resource manager instance
	ResourceManager resource_manager {mediator};

	//! Component manager instance
	ComponentManager component_manager {mediator};
	//! Scene manager instance
	SceneManager scene_manager {mediator};
	//! LoopTimerManager instance
	LoopTimerManager loop_timer {mediator};
	//! EventManager instance
	EventManager event_manager {mediator};
	//! Save manager instance
	SaveManager save_manager {mediator};
	//! ReplayManager instance
	ReplayManager replay_manager {mediator};
};

} // namespace crepe

#include "Engine.hpp"
