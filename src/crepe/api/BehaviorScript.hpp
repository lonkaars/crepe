#pragma once

#include <type_traits>

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <class T, typename... Args>
BehaviorScript & BehaviorScript::set_script(Args &&... args) {
	static_assert(std::is_base_of<Script, T>::value);
	this->script = std::unique_ptr<Script>(new T(std::forward<Args>(args)...));

	this->script->game_object_id = this->game_object_id;
	this->script->active = this->active;
	this->script->mediator = this->mediator;

	return *this;
}

} // namespace crepe
