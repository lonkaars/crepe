#pragma once

#include <stdexcept>
#include <type_traits>

#include "../util/log.h"

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <class T>
BehaviorScript & BehaviorScript::set_script() {
	if (this == nullptr) {
		throw std::runtime_error("BehaviorScript instance is NULL");
	}
	static_assert(std::is_base_of<Script, T>::value, "T must derive from Script");
	dbg_trace();
	Script * s = new T();
	s->parent = this;
	this->script = std::unique_ptr<Script>(s);
	return *this;
}

} // namespace crepe
