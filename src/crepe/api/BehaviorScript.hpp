#pragma once

#include <type_traits>

#include "../util/Log.h"

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <class T, typename... Args>
BehaviorScript & BehaviorScript::set_script(Args &&... args) {
	dbg_trace();
	static_assert(std::is_base_of<Script, T>::value);
	Script * s = new T(std::forward<Args>(args)...);
	s->game_object_id = this->game_object_id;
	s->active = this->active;
	s->component_manager = this->component_manager;
	s->event_manager = EventManager::get_instance();

	this->script = std::unique_ptr<Script>(s);
	return *this;
}

} // namespace crepe
