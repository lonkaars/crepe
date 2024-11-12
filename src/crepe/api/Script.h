#pragma once

#include <vector>

namespace crepe {
class ScriptSystem;
}

namespace crepe {

class BehaviorScript;

class Script {
	//! ScriptSystem calls \c update()
	friend class crepe::ScriptSystem;

protected:
	virtual void init() {}
	virtual void update() {}
	// NOTE: additional *events* (like unity's OnDisable and OnEnable) should be
	// implemented as member methods in derivative user script classes and
	// registered in init(), otherwise this class will balloon in size with each
	// added event.

protected:
	//! Retrieve component from component manager (utility)
	template <typename T>
	T & get_component();

	//! Retrieve components from component manager (utility)
	template <typename T>
	std::vector<std::reference_wrapper<T>> get_components();

protected:
	// NOTE: Script must have a constructor without arguments so the game
	// programmer doesn't need to manually add `using Script::Script` to their
	// concrete script class.
	Script() = default;
	//! Only \c BehaviorScript instantiates Script
	friend class BehaviorScript;
	BehaviorScript * parent_ref = nullptr;
};

} // namespace crepe

#include "Script.hpp"

