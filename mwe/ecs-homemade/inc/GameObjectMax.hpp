#include "ComponentManager.h"

template <typename T, typename... Args>
T & GameObject::AddComponent(Args &&... args) {
	return ComponentManager::GetInstance().AddComponent<T>(
		mId, std::forward<Args>(args)...);
}
