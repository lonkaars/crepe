#pragma once

#include <type_traits>

#include "../util/Log.h"

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <class T>
BehaviorScript & BehaviorScript::set_script() {
	dbg_trace();
	static_assert(std::is_base_of<Script, T>::value);
	Script * s = new T();
	s->parent_ref = this;
	s->component_manager_ref = &this->component_manager;
	this->script = std::unique_ptr<Script>(s);
	return *this;
}

} // namespace crepe
