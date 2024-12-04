#pragma once

#include "../manager/ComponentManager.h"

#include "GameObject.h"

namespace crepe {

template <typename T, typename... Args>
T & GameObject::add_component(Args &&... args) {
	ComponentManager & mgr = this->component_manager;
	return mgr.add_component<T>(this->id, std::forward<Args>(args)...);
}

} // namespace crepe
