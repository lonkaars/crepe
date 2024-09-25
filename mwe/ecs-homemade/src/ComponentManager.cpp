#include "ComponentManager.h"

ComponentManager ComponentManager::mInstance;

ComponentManager& ComponentManager::GetInstance() {
	return mInstance;
}

ComponentManager::ComponentManager() {}
