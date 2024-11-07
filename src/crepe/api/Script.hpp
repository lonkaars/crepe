#pragma once

#include "../ComponentManager.h"

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <typename T>
T & Script::get_component() {
	std::vector<std::reference_wrapper<T>> all_components
		= this->get_components<T>();
	if (all_components.size() < 1) throw nullptr; // TODO

	return all_components.back().get();
}

template <typename T>
std::vector<std::reference_wrapper<T>> Script::get_components() {
	ComponentManager & mgr = ComponentManager::get_instance();
	return mgr.get_components_by_id<T>(this->parent->GAME_OBJECT_ID);
}

} // namespace crepe
