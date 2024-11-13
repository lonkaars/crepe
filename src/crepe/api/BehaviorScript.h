#pragma once

#include <memory>

#include "../Component.h"

namespace crepe {

class ScriptSystem;
class ComponentManager;
class Script;

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
	std::unique_ptr<Script> script = nullptr;
};

} // namespace crepe

#include "BehaviorScript.hpp"
