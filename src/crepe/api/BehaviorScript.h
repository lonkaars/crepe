#pragma once

#include <memory>

#include "../Component.h"

namespace crepe {

class ScriptSystem;
class ComponentManager;
class Script;

class BehaviorScript : public Component {
protected:
	BehaviorScript(game_object_id_t id, ComponentManager & component_manager);
	//! Only ComponentManager is allowed to instantiate BehaviorScript
	friend class ComponentManager;

public:
	virtual ~BehaviorScript() = default;

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
	std::unique_ptr<Script> script = nullptr;
	ComponentManager & component_manager;

private:
	//! Script accesses the component manager directly via its parent
	// (BehaviorScript) reference
	friend class Script;
};

} // namespace crepe

#include "BehaviorScript.hpp"
