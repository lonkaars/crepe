#pragma once

#include <memory>

#include "../Component.h"

namespace crepe {
class ScriptSystem;
class ComponentManager;
} // namespace crepe

namespace crepe::api {

class Script;

class BehaviorScript : public Component {
protected:
	friend class crepe::ComponentManager;
	BehaviorScript();

public:
	virtual ~BehaviorScript() = default;

public:
	template <class T>
	BehaviorScript & set_script();

protected:
	friend class crepe::ScriptSystem;
	std::unique_ptr<Script> script = nullptr;
};

} // namespace crepe::api

#include "BehaviorScript.hpp"
