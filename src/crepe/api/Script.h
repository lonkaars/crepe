#pragma once

#include <vector>

namespace crepe {
class ScriptSystem;
}

namespace crepe {

class BehaviorScript;

class Script {
	friend class crepe::ScriptSystem;

protected:
	virtual void init() {}
	virtual void update() {}
	// NOTE: additional *events* (like unity's OnDisable and OnEnable) should be
	// implemented as member methods in derivative user script classes and
	// registered in init(), otherwise this class will balloon in size with each
	// added event.

protected:
	template <typename T>
	T & get_component();

	template <typename T>
	std::vector<std::reference_wrapper<T>> get_components();

private:
	friend class crepe::BehaviorScript;
	BehaviorScript * parent = nullptr;
};

} // namespace crepe

#include "Script.hpp"
