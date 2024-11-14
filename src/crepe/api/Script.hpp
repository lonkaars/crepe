#pragma once

#include "../ComponentManager.h"
#include "../Exception.h"

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <typename T>
T & Script::get_component() const {
	std::vector<std::reference_wrapper<T>> all_components
		= this->get_components<T>();
	if (all_components.size() < 1)
		throw Exception("Script: no component found with type = {}",
						typeid(T).name());

	return all_components.back().get();
}

template <typename T>
std::vector<std::reference_wrapper<T>> Script::get_components() const {
	auto & parent = *this->parent_ref;
	auto & mgr = *this->component_manager_ref;

	return mgr.get_components_by_id<T>(parent.game_object_id);
}

} // namespace crepe
