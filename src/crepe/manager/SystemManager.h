#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "../system/System.h"

#include "Manager.h"

namespace crepe {

/**
 * \brief Collection of all systems
 *
 * This manager aggregates all systems and provides utility functions to retrieve references to
 * and update systems.
 */
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

public:
	/**
	 * \brief SystemManager snapshot
	 *
	 * The SystemManager snapshot only stores which systems are active
	 */
	typedef std::unordered_map<std::type_index, bool> Snapshot;
	/**
	 * \brief Save a snapshot of the systems' state
	 * \returns Copy of each system's active property
	 */
	Snapshot save();
	/**
	 * \brief Restore system active state from a snapshot
	 * \param snapshot Snapshot to restore from (as returned by \c save())
	 */
	void restore(const Snapshot & snapshot);
	//! Disable all systems
	void disable_all();
};

} // namespace crepe

#include "SystemManager.hpp"
