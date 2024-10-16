#pragma once

#include "../Component.h"

namespace crepe {
class ScriptSystem;
class ComponentManager;
}

namespace crepe::api {

class Script;

class BehaviorScript : public Component {
protected:
	friend class crepe::ComponentManager;
	BehaviorScript();
public:
	virtual ~BehaviorScript() = default;

public:
	template<class T>
	BehaviorScript & set_script();

protected:
	friend class crepe::ScriptSystem;
	Script * script = nullptr;
};

}

#include "BehaviorScript.hpp"

