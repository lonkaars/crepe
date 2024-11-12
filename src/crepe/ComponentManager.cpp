#include "api/GameObject.h"
#include "util/log.h"

#include "ComponentManager.h"

using namespace crepe;
using namespace std;

void ComponentManager::delete_all_components_of_id(game_object_id_t id) {
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
	// Clear the whole unordered_map<>
	this->components.clear();
}

ComponentManager::ComponentManager() { dbg_trace(); }
ComponentManager::~ComponentManager() { dbg_trace(); }

GameObject & ComponentManager::new_object(const string & name, const string & tag, const Vector2 & position, double rotation, double scale) {
	GameObject * object = new GameObject(*this, this->next_id, name, tag, position, rotation, scale);
	this->objects.push_front(unique_ptr<GameObject>(object));
	this->next_id++;
	return *object;
}

