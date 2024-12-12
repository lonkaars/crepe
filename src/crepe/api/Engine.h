#pragma once

#include "../facade/SDLContext.h"
#include "../manager/ComponentManager.h"
#include "../manager/ReplayManager.h"
#include "../manager/ResourceManager.h"
#include "../manager/ResourceManager.h"
#include "../manager/SaveManager.h"
#include "../manager/SceneManager.h"
#include "../manager/SystemManager.h"
#include "../manager/LoopTimerManager.h"
#include "../manager/EventManager.h"

namespace crepe {

/**
 * \brief Main game entrypoint
 *
 * This class is responsible for managing the game loop, including initialization and updating.
 */
class Engine {
public:
	void start();

	/**
	 * \brief Add a new concrete scene to the scene manager
	 *
	 * \tparam T  Type of concrete scene
	 */
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

	bool game_running = false;

private:
	//! Global context
	Mediator mediator;

	//! Component manager instance
	ComponentManager component_manager{mediator};
	//! Scene manager instance
	SceneManager scene_manager{mediator};
	//! LoopTimerManager instance
	LoopTimerManager loop_timer{mediator};
	//! EventManager instance
	EventManager event_manager{mediator};
	//! Resource manager instance
	ResourceManager resource_manager{mediator};
	//! Save manager instance
	SaveManager save_manager{mediator};
	//! SDLContext instance
	SDLContext sdl_context{mediator};
	//! ReplayManager instance
	ReplayManager replay_manager{mediator};
	//! SystemManager
	SystemManager system_manager{mediator};
};

} // namespace crepe

#include "Engine.hpp"
