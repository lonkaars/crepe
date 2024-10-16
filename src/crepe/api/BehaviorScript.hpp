#pragma once

#include <type_traits>

#include "../util/log.h"
#include "BehaviorScript.h"

namespace crepe::api {

template<class T>
BehaviorScript & BehaviorScript::set_script() {
	static_assert(std::is_base_of<Script, T>::value);
	dbg_trace();
	this->script = new T();
	return *this;
}

}
