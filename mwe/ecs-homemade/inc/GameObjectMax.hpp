#include "ComponentManager.h"

template <typename T>
void GameObject::AddComponent(T* component) {
	ComponentManager::GetInstance().AddComponent(component, mId);
}
