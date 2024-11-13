#pragma once

#include <memory>

#include "../Component.h"

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
	friend class crepe::ComponentManager;
	using Component::Component;

public:
	~BehaviorScript() = default;

public:
	template <class T>
	BehaviorScript & set_script();

protected:
	friend class crepe::ScriptSystem;
	//! Script instance
	std::unique_ptr<Script> script = nullptr;
};

} // namespace crepe

#include "BehaviorScript.hpp"
