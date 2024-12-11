#pragma once

#include <memory>
#include <cassert>
#include <format>

#include "SystemManager.h"

namespace crepe {

template <class T>
T & SystemManager::get_system() {
	using namespace std;
	static_assert(is_base_of<System, T>::value, "get_system must recieve a derivative class of System");

	const type_info & type = typeid(T);
	if (!this->systems.contains(type))
		throw runtime_error(format("SystemManager: {} is not initialized", type.name()));

	System * system = this->systems.at(type).get();
	T * concrete_system = dynamic_cast<T *>(system);
	assert(concrete_system != nullptr);

	return *concrete_system;
}

template <class T>
void SystemManager::load_system() {
	using namespace std;
	static_assert(is_base_of<System, T>::value,
			"load_system must recieve a derivative class of System");

	const type_info & type = typeid(T);
	if (this->systems.contains(type))
		throw runtime_error(format("SystemManager: {} is already initialized", type.name()));
	System * system = new T(this->mediator);
	this->systems[type] = unique_ptr<System>(system);
}

} // namespace crepe
