#pragma once

#include <cassert>
#include <format>
#include <memory>

#include "../system/System.h"

#include "LoopManager.h"

namespace crepe {

template <class T>
void LoopManager::add_scene() {
	this->scene_manager.add_scene<T>();
}

template <class T>
T & LoopManager::get_system() {
	using namespace std;
	static_assert(is_base_of<System, T>::value,
				  "get_system must recieve a derivative class of System");

	const type_info & type = typeid(T);
	if (!this->systems.contains(type))
		throw runtime_error(format("LoopManager: {} is not initialized", type.name()));

	System * system = this->systems.at(type).get();
	T * concrete_system = dynamic_cast<T *>(system);
	assert(concrete_system != nullptr);

	return *concrete_system;
}

template <class T>
void LoopManager::load_system() {
	using namespace std;
	static_assert(is_base_of<System, T>::value,
				  "load_system must recieve a derivative class of System");

	System * system = new T(this->component_manager);
	this->systems[typeid(T)] = unique_ptr<System>(system);
}

} // namespace crepe
