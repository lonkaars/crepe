#pragma once

#include <type_traits>

#include "../util/log.h"

#include "BehaviorScript.h"

namespace crepe::api {

template <class T>
BehaviorScript & BehaviorScript::set_script() {
	static_assert(std::is_base_of<Script, T>::value);
	dbg_trace();
	Script * s = new T();
	this->script = std::unique_ptr<Script>(s);
	return *this;
}

} // namespace crepe::api
