#pragma once

#include <memory>

#include "../facade/SDLContext.h"
#include "../manager/ComponentManager.h"
#include "../manager/SceneManager.h"
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
	 * \brief Function for handling input-related system calls.
	 *
	 * Processes user inputs from keyboard and mouse.
	 */
	void process_input();

	/**
	 * \brief Per-frame update.
	 *
	 * Updates the game state based on the elapsed time since the last frame.
	 */
	void update();

	/**
	 * \brief Late update which is called after update().
	 *
	 * This function can be used for final adjustments before rendering.
	 */
	void late_update();

	/**
	 * \brief Fixed update executed at a fixed rate.
	 *
	 * This function updates physics and game logic based on LoopTimer's fixed_delta_time.
	 */
	void fixed_update();

	/**
	 * \brief Set game running variable
	 *
	 * \param running running (false = game shutdown, true = game running)
	 */
	void set_running(bool running);

	/**
	 * \brief Function for executing render-related systems.
	 *
	 * Renders the current state of the game to the screen.
	 */
	void render();

	bool game_running = false;

private:
	//! Global context
	Mediator mediator;

	//! Component manager instance
	ComponentManager component_manager{mediator};
	//! Scene manager instance
	SceneManager scene_manager{mediator};

	//! SDL context \todo no more singletons!
	SDLContext & sdl_context = SDLContext::get_instance();
	//! Loop timer \todo no more singletons!
	LoopTimer & loop_timer = LoopTimer::get_instance();

private:
	/**
	 * \brief Collection of System instances
	 *
	 * This map holds System instances indexed by the system's class typeid. It is filled in the
	 * constructor of \c LoopManager using LoopManager::load_system.
	 */
	std::unordered_map<std::type_index, std::unique_ptr<System>> systems;
	/**
	 * \brief Initialize a system
	 * \tparam T System type (must be derivative of \c System)
	 */
	template <class T>
	void load_system();
	/**
	 * \brief Retrieve a reference to ECS system
	 * \tparam T System type
	 * \returns Reference to system instance
	 * \throws std::runtime_error if the System is not initialized
	 */
	template <class T>
	T & get_system();
};

} // namespace crepe

#include "LoopManager.hpp"
