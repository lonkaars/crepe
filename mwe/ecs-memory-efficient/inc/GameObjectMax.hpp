#include "ComponentManager.h"

template <typename... Args>
void GameObject::addSpriteComponent(Args &&... args) {
	ComponentManager::GetInstance().addSpriteComponent(std::forward<Args>(args)...);
}

template <typename... Args>
void GameObject::addRigidbodyComponent(Args &&... args) {
	ComponentManager::GetInstance().addRigidbodyComponent(std::forward<Args>(args)...);
}

template <typename... Args>
void GameObject::addColiderComponent(Args &&... args) {
	ComponentManager::GetInstance().addColiderComponent(std::forward<Args>(args)...);
}
