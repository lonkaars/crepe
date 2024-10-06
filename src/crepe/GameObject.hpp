#pragma once

#include "GameObject.h"

#include "ComponentManager.h"

namespace crepe {

template <typename T, typename... Args>
void GameObject::AddComponent(Args &&... args) {
	ComponentManager::get_instance().AddComponent<T>(mId, std::forward<Args>(args)...);
}

}

