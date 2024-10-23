#pragma once

#include "../ComponentManager.h"

#include "GameObject.h"

namespace crepe::api {

template <typename T, typename... Args>
T & GameObject::add_component(Args &&... args) {
	auto & mgr = ComponentManager::get_instance();
	return mgr.add_component<T>(id, std::forward<Args>(args)...);
}

} // namespace crepe::api
