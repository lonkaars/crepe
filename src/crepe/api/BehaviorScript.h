#pragma once

#include <memory>

#include "../Component.h"

#include "GameObject.h"

namespace crepe {

class ScriptSystem;
class ComponentManager;
class Script;

/**
 * \brief Script component
 *
 * This class acts as a (component) wrapper around an instance of (a class derivatived from) \c
 * Script. \c BehaviorScript is the only ECS component that stores member function
 * implementations as data.
 */
class BehaviorScript : public Component {
protected:
	/**
	 * \param id Parent \c GameObject id
	 * \param component_manager Reference to component manager (passed through to \c Script
	 * instance)
	 *
	 * \note Calls to this constructor (should) always pass through \c GameObject::add_component,
	 * which has an exception for this specific component type. This was done so the user does
	 * not have to pass references used within \c Script to each \c BehaviorScript instance.
	 */
	BehaviorScript(game_object_id_t id, ComponentManager & component_manager);
	//! Only ComponentManager is allowed to instantiate BehaviorScript
	friend class ComponentManager;

public:
	/**
	 * \brief Set the concrete script of this component
	 *
	 * \tparam T Concrete script type (derived from \c crepe::Script)
	 * \tparam Args Arguments for concrete script constructor
	 *
	 * \param args Arguments for concrete script constructor (forwarded using perfect forwarding)
	 *
	 * \returns Reference to BehaviorScript component (`*this`)
	 */
	template <class T, typename... Args>
	BehaviorScript & set_script(Args &&... args);

protected:
	//! Script instance
	std::unique_ptr<Script> script = nullptr;
	//! ScriptSystem needs direct access to the script instance
	friend class ScriptSystem;

protected:
	//! Reference to component manager (passed to Script)
	ComponentManager & component_manager;
};

/**
 * \brief Add a BehaviorScript component to this game object
 *
 * The \c BehaviorScript class is the only exception to the ECS harmony, and requires a
 * reference to the component manager passed to its constructor in order to function normally.
 * This is because the \c BehaviorScript (and \c Script) classes are the only component-related
 * classes that store implemented member functions as data.
 */
template <>
BehaviorScript & GameObject::add_component<BehaviorScript>();

} // namespace crepe

#include "BehaviorScript.hpp"
