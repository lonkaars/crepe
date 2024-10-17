#include "ComponentManager.h"

ComponentManager ComponentManager::mInstance;

ComponentManager& ComponentManager::GetInstance() {
	return mInstance;
}

ComponentManager::ComponentManager() {}

std::vector<std::reference_wrapper<Sprite>> ComponentManager::getAllSpriteReferences() {
	return mSpriteContainer.getAllReferences();
}

std::vector<std::reference_wrapper<Rigidbody>> ComponentManager::getAllRigidbodyReferences() {
	return mRigidbodyContainer.getAllReferences();
}

std::vector<std::reference_wrapper<Colider>> ComponentManager::getAllColiderReferences() {
	return mColiderContainer.getAllReferences();
}
