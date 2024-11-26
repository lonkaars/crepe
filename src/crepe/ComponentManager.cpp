#include "api/GameObject.h"
#include "util/Log.h"

#include "ComponentManager.h"
#include "types.h"

using namespace crepe;
using namespace std;

ComponentManager::ComponentManager() { dbg_trace(); }
ComponentManager::~ComponentManager() { dbg_trace(); }

void ComponentManager::delete_all_components_of_id(game_object_id_t id) {
	// Do not delete persistent objects
	if (this->persistent[id]) {
		return;
	}

	// Loop through all the types (in the unordered_map<>)
	for (auto & [type, componentArray] : this->components) {
		// Make sure that the id (that we are looking for) is within the boundaries of the vector<>
		if (id < componentArray.size()) {
			// Clear the components at this specific id
			componentArray[id].clear();
		}
	}
}

void ComponentManager::delete_all_components() {
	// Loop through all the ids and delete all components of each id
	for (game_object_id_t id = 0; id < next_id; id++) {
		delete_all_components_of_id(id);
	}
	this->next_id = 0;
}

GameObject ComponentManager::new_object(const string & name, const string & tag,
										const vec2 & position, double rotation, double scale) {
	// Find the first available id (taking persistent objects into account)
	while (this->persistent[this->next_id]) {
		this->next_id++;
	}

	GameObject object{*this, this->next_id, name, tag, position, rotation, scale};
	this->next_id++;

	return object;
}

void ComponentManager::set_persistent(game_object_id_t id) { this->persistent[id] = true; }
