#include "util/log.h"

#include "ComponentManager.h"

using namespace crepe;

ComponentManager & ComponentManager::get_instance() {
	static ComponentManager instance;
	return instance;
}

void ComponentManager::delete_all_components_of_id(uint32_t id) {
	// Loop through all the types (in the unordered_map<>)
	for (auto & [type, componentArray] : components) {
		// Make sure that the id (that we are looking for) is within the boundaries of the vector<>
		if (id < componentArray.size()) {
			// Clear the components at this specific id
			componentArray[id].clear();
		}
	}
}

void ComponentManager::delete_all_components() {
	// Clear the whole unordered_map<>
	this->components.clear();
}

ComponentManager::ComponentManager() { dbg_trace(); }

ComponentManager::~ComponentManager() { dbg_trace(); }
