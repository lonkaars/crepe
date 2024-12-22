#include "ComponentManager.h"

ComponentManager ComponentManager::mInstance;

ComponentManager & ComponentManager::GetInstance() { return mInstance; }

ComponentManager::ComponentManager() {}

void ComponentManager::DeleteAllComponentsOfId(std::uint32_t id) {
	for (auto & [type, componentArray] :
		 mComponents) { //Loop through all the types (in the unordered_map<>)
		if (id < componentArray.size(
			)) { //Make sure that the id (that we are looking for) is within the boundaries of the vector<>
			componentArray[id].clear(); //Clear the components at this specific id
		}
	}
}

void ComponentManager::DeleteAllComponents() {
	mComponents.clear(); //Clear the whole unordered_map<>
}
