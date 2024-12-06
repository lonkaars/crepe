#include "../api/GameObject.h"
#include "../api/Metadata.h"
#include "../types.h"
#include "../util/Log.h"

#include "ComponentManager.h"

using namespace crepe;
using namespace std;

ComponentManager::ComponentManager(Mediator & mediator) : Manager(mediator) {
	mediator.component_manager = *this;
	dbg_trace();
}
ComponentManager::~ComponentManager() { dbg_trace(); }

void ComponentManager::delete_all_components_of_id(game_object_id_t id) {
	// Do not delete persistent objects
	if (this->persistent[id]) {
		return;
	}

	// Loop through all the types (in the unordered_map<>)
	for (auto & [type, component_array] : this->components) {
		// Make sure that the id (that we are looking for) is within the boundaries of the vector<>
		if (id < component_array.size()) {
			// Clear the components at this specific id
			component_array[id].clear();
		}
	}
}

void ComponentManager::delete_all_components() {
	// Loop through all the types (in the unordered_map<>)
	for (auto & [type, component_array] : this->components) {
		// Loop through all the ids (in the vector<>)
		for (game_object_id_t id = 0; id < component_array.size(); id++) {
			// Do not delete persistent objects
			if (!this->persistent[id]) {
				// Clear the components at this specific id
				component_array[id].clear();
			}
		}
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

void ComponentManager::set_persistent(game_object_id_t id, bool persistent) {
	this->persistent[id] = persistent;
}

set<game_object_id_t> ComponentManager::get_objects_by_name(const string & name) const {
	return this->get_objects_by_predicate<Metadata>([name](const Metadata & data) {
		return data.name == name;
	});
}

set<game_object_id_t> ComponentManager::get_objects_by_tag(const string & tag) const {
	return this->get_objects_by_predicate<Metadata>([tag](const Metadata & data) {
		return data.tag == tag;
	});
}

