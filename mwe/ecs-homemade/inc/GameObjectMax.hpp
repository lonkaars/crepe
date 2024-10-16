#include "ComponentManager.h"

template <typename T, typename... Args>
void GameObject::AddComponent(Args &&... args) {
	ComponentManager::GetInstance().AddComponent<T>(
		mId, std::forward<Args>(args)...);
}
