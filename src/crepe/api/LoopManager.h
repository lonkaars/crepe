#pragma once

#include "../facade/SDLContext.h"
#include "../manager/ComponentManager.h"
#include "../manager/ResourceManager.h"
#include "../manager/SceneManager.h"
#include "../manager/SaveManager.h"
#include "../system/System.h"

#include "LoopTimer.h"

namespace crepe {

/**
 * \brief Main game loop manager
 *
 * This class is responsible for managing the game loop, including initialization and updating.
 */
class LoopManager {
public:
	void start();
	LoopManager();

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

	/**
	 * \brief Per-frame update.
	 *
	 * Updates the game state based on the elapsed time since the last frame.
	 */
	void frame_update();

	/**
	 * \brief Fixed update executed at a fixed rate.
	 *
	 * This function updates physics and game logic based on LoopTimer's fixed_delta_time.
	 */
	void fixed_update();

	bool game_running = false;

private:
	//! Global context
	Mediator mediator;

	//! Component manager instance
	ComponentManager component_manager{mediator};
	//! Scene manager instance
	SceneManager scene_manager{mediator};
	//! Resource manager instance
	ResourceManager resource_manager{mediator};
	//! Save manager instance
	SaveManager save_manager{mediator};

	//! SDL context \todo no more singletons!
	SDLContext & sdl_context = SDLContext::get_instance();
	//! Loop timer \todo no more singletons!
	LoopTimer & loop_timer = LoopTimer::get_instance();

private:
	/**
	 * \brief Collection of System instances
	 */
	std::vector<System> systems;
};

} // namespace crepe

#include "LoopManager.hpp"
