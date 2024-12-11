#pragma once

#include "../facade/SDLContext.h"
#include "../manager/ComponentManager.h"
#include "../manager/ReplayManager.h"
#include "../manager/ResourceManager.h"
#include "../manager/ResourceManager.h"
#include "../manager/SaveManager.h"
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
	//! SDLContext instance
	SDLContext sdl_context{mediator};
	//! LoopTimer instance
	LoopTimer loop_timer{mediator};
	//! ReplayManager instance
	ReplayManager replay_manager{mediator};

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
