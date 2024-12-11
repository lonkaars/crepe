#pragma once

#include "../system/System.h"

#include "Manager.h"

namespace crepe {

class SystemManager : public Manager {
public:
	SystemManager(Mediator &);

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

private:
	/**
	 * \brief Collection of System instances
	 *
	 * This map holds System instances indexed by the system's class typeid. It is filled in the
	 * constructor of \c SystemManager using SystemManager::load_system.
	 */
	std::unordered_map<std::type_index, std::unique_ptr<System>> systems;
	/**
	 * \brief Initialize a system
	 * \tparam T System type (must be derivative of \c System)
	 */
	template <class T>
	void load_system();

public:
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

#include "SystemManager.hpp"
