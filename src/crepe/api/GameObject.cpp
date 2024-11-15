#include "api/Transform.h"

#include "GameObject.h"
#include "Metadata.h"

using namespace crepe;
using namespace std;

GameObject::GameObject(game_object_id_t id, const std::string & name, const std::string & tag,
					   const Vector2 & position, double rotation, double scale)
	: id(id) {
	// Add Transform and Metadata components
	ComponentManager & mgr = ComponentManager::get_instance();
	mgr.add_component<Transform>(this->id, position, rotation, scale);
	mgr.add_component<Metadata>(this->id, name, tag);
}

void GameObject::set_parent(const GameObject & parent) {
	ComponentManager & mgr = ComponentManager::get_instance();

	// Set parent on own Metadata component
	vector<reference_wrapper<Metadata>> this_metadata
		= mgr.get_components_by_id<Metadata>(this->id);
	this_metadata.at(0).get().parent = parent.id;

	// Add own id to children list of parent's Metadata component
	vector<reference_wrapper<Metadata>> parent_metadata
		= mgr.get_components_by_id<Metadata>(parent.id);
	parent_metadata.at(0).get().children.push_back(this->id);
}
