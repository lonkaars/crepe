#pragma once

#include <memory>

#include "../facade/SDLContext.h"
#include "../manager/ComponentManager.h"
#include "../manager/EventManager.h"
#include "../manager/LoopTimerManager.h"
#include "../manager/Mediator.h"
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
	LoopManager();
	/**
	 * \brief Start the gameloop
	 *
	 * This is the start of the engine where the setup is called and then the loop keeps running until the game stops running.
	 * The Game programmer needs to call this function to run the game. This should be done after creating and adding all scenes.
	 */
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

	/**
	 * \brief Per-frame update.
	 *
	 * Updates the game state based on the elapsed time since the last frame.
	 */
	virtual void frame_update();

	/**
	 * \brief Fixed update executed at a fixed rate.
	 *
	 * This function updates physics and game logic based on LoopTimer's fixed_delta_time.
	 */
	virtual void fixed_update();

	//! Indicates whether the game is running.
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

private:
	/**
	 * \brief Callback function for ShutDownEvent
	 *
	 * This function sets the game_running variable to false, stopping the gameloop and therefor quitting the game.
	 */
	bool on_shutdown(const ShutDownEvent & e);
	/**
	 * \brief Collection of System instances
	 *
	 * This map holds System instances indexed by the system's class typeid. It is filled in the
	 * constructor of LoopManager using LoopManager::load_system.
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
