#pragma once

#include <memory>

#include "../system/System.h"
#include "../ComponentManager.h"

namespace crepe {

class LoopManager {
public:
	void start();
	LoopManager();

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

protected:
	ComponentManager & get_component_manager();
	template <class T>
	T & get_system();

private:
	ComponentManager component_manager;
	std::unordered_map<std::type_index, std::unique_ptr<System>> systems;

private:
	template <class T>
	void load_system();
};

} // namespace crepe

#include "LoopManager.hpp"

