#pragma once

#include <memory>

#include "Component.h"

namespace crepe {

class ScriptSystem;
class ComponentManager;
class Script;

class BehaviorScript : public Component {
protected:
	friend class ComponentManager;
	using Component::Component;

public:
	virtual ~BehaviorScript() = default;

public:
	template <class T>
	BehaviorScript & set_script();

public:
	virtual int get_instances_max() const { return 10; }

protected:
	friend class ScriptSystem;
	std::unique_ptr<Script> script = nullptr;
};

} // namespace crepe

#include "BehaviorScript.hpp"
