#pragma once

#include "GameObject.h"

#include "ComponentManager.h"

namespace crepe {

template <typename T, typename... Args>
void GameObject::add_component(Args &&... args) {
	auto & mgr = ComponentManager::get_instance();
	mgr.add_component<T>(id, std::forward<Args>(args)...);
}

} // namespace crepe
