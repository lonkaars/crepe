#pragma once

#include <vector>

#include "../types.h"

namespace crepe {

class ScriptSystem;
class BehaviorScript;
class ComponentManager;

/**
 * \brief Script interface
 *
 * This class is used as a base class for user-defined scripts that can be added to game
 * objects using the \c BehaviorScript component.
 *
 * \note Additional *events* (like Unity's OnDisable and OnEnable) should be implemented as
 * member or lambda methods in derivative user script classes and registered in \c init().
 */
class Script {
protected:
	/**
	 * \name Interface functions
	 * \{
	 */
	/**
	 * \brief Script initialization function (empty by default)
	 *
	 * This function is called during the ScriptSystem::update() routine *before*
	 * Script::update() if it (a) has not yet been called and (b) the \c BehaviorScript component
	 * holding this script instance is active.
	 */
	virtual void init() {}
	/**
	 * \brief Script update function (empty by default)
	 *
	 * This function is called during the ScriptSystem::update() routine if the \c BehaviorScript
	 * component holding this script instance is active.
	 */
	virtual void update() {}
	//! \}

	//! ScriptSystem calls \c init() and \c update()
	friend class crepe::ScriptSystem;

protected:
	/**
	 * \name Utility functions
	 * \{
	 */

	/**
	 * \brief Get single component of type \c T on this game object
	 *
	 * \tparam T Type of component
	 *
	 * \returns Reference to component
	 *
	 * \throws std::runtime_error if this game object does not have a component matching type \c
	 * T
	 */
	template <typename T>
	T & get_component() const;
	// TODO: make get_component calls for component types that can have more than 1 instance
	// cause compile-time errors

	/**
	 * \brief Get all components of type \c T on this game object
	 *
	 * \tparam T Type of component
	 *
	 * \returns List of component references
	 */
	template <typename T>
	std::vector<std::reference_wrapper<T>> get_components() const;

	/**
	 * \brief Log a message using Log::logf
	 *
	 * \tparam Args Log::logf parameters
	 * \param args  Log::logf parameters
	 */
	template <typename... Args>
	void logf(Args &&... args);

	//! \}

protected:
	// NOTE: Script must have a constructor without arguments so the game programmer doesn't need
	// to manually add `using Script::Script` to their concrete script class.
	Script() = default;
	//! Only \c BehaviorScript instantiates Script
	friend class BehaviorScript;

private:
	// These references are set by BehaviorScript immediately after calling the constructor of
	// Script.
	game_object_id_t game_object_id = -1;
	ComponentManager * component_manager_ref = nullptr;
	// TODO: use OptionalRef instead of pointer

private:
	//! Flag to indicate if \c init() has been called already
	bool initialized = false;
};

} // namespace crepe

#include "Script.hpp"
