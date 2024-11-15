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
 * This class acts as a (component) wrapper around an instance of (a class
 * derivatived from) \c Script. \c BehaviorScript is the only ECS component
 * that stores member function implementations as data.
 */
class BehaviorScript : public Component {
protected:
	BehaviorScript(game_object_id_t id, ComponentManager & component_manager);
	//! Only ComponentManager is allowed to instantiate BehaviorScript
	friend class ComponentManager;

public:
	~BehaviorScript() = default;

public:
	/**
	 * \brief Set the concrete script of this component
	 *
	 * \tparam T Concrete script type (derived from \c crepe::Script)
	 *
	 * \returns Reference to BehaviorScript component (`*this`)
	 */
	template <class T>
	BehaviorScript & set_script();

protected:
	//! ScriptSystem needs direct access to the script instance
	friend class ScriptSystem;
	//! Flag to indicate if script->init() has been called already
	bool initialized = false;
	//! Script instance
	std::unique_ptr<Script> script = nullptr;
	//! Reference to component manager
	ComponentManager & component_manager;
	//! Script accesses the component manager directly via its parent
	// (BehaviorScript) reference
	friend class Script;
};

/**
 * \brief Add a BehaviorScript component to this game object
 *
 * The \c BehaviorScript class is the only exception to the ECS harmony, and
 * requires a reference to the component manager passed to its constructor in
 * order to function normally. This is because the \c BehaviorScript (and \c
 * Script) classes are the only component-related classes that store
 * implemented member functions as data.
 */
template <>
BehaviorScript & GameObject::add_component<BehaviorScript>();

} // namespace crepe

#include "BehaviorScript.hpp"
