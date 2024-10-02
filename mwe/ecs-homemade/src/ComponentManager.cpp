#include "ComponentManager.h"

ComponentManager ComponentManager::mInstance;

ComponentManager& ComponentManager::GetInstance() {
	return mInstance;
}

ComponentManager::ComponentManager() {}

void ComponentManager::DeleteAllComponentsOfId(std::uint32_t id) {

}

void ComponentManager::DeleteAllComponents() {
	mComponents.clear();
}
