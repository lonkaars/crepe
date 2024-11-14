#pragma once

#include <vector>

namespace crepe {

class ScriptSystem;
class BehaviorScript;
class ComponentManager;

/**
 * \brief Script interface
 *
 * This class is used as a base class for user-defined scripts that can be
 * added to game objects using the \c BehaviorScript component.
 */
class Script {
	//! ScriptSystem calls \c update()
	friend class crepe::ScriptSystem;

protected:
	/**
	 * \brief Script initialization function
	 *
	 * This function is called during the ScriptSystem::update() routine *before*
	 * Script::update() if it (a) has not yet been called and (b) the \c
	 * BehaviorScript component holding this script instance is active.
	 */
	virtual void init() {}
	/**
	 * \brief Script update function
	 *
	 * This function is called during the ScriptSystem::update() routine if the
	 * \c BehaviorScript component holding this script instance is active.
	 */
	virtual void update() {}
	// NOTE: additional *events* (like unity's OnDisable and OnEnable) should be
	// implemented as member methods in derivative user script classes and
	// registered in init(), otherwise this class will balloon in size with each
	// added event.

protected:
	/**
	 * \brief Get single component of type \c T on this game object (utility)
	 *
	 * \tparam T Type of component
	 *
	 * \returns Reference to component
	 *
	 * \throws nullptr if this game object does not have a component matching
	 * type \c T
	 */
	template <typename T>
	T & get_component() const;

	/**
	 * \brief Get all components of type \c T on this game object (utility)
	 *
	 * \tparam T Type of component
	 *
	 * \returns List of component references
	 */
	template <typename T>
	std::vector<std::reference_wrapper<T>> get_components() const;

protected:
	// NOTE: Script must have a constructor without arguments so the game
	// programmer doesn't need to manually add `using Script::Script` to their
	// concrete script class.
	Script() = default;
	//! Only \c BehaviorScript instantiates Script
	friend class BehaviorScript;

private:
	// These references are set by BehaviorScript immediately after calling the
	// constructor of Script.
	BehaviorScript * parent_ref = nullptr;
	ComponentManager * component_manager_ref = nullptr;
};

} // namespace crepe

#include "Script.hpp"
