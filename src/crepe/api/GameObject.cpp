#include "api/Transform.h"

#include "GameObject.h"
#include "Metadata.h"

using namespace crepe;
using namespace std;

GameObject::GameObject(uint32_t id, std::string name, std::string tag,
					   const Point & position, double rotation, double scale)
	: id(id) {
	ComponentManager & mgr = ComponentManager::get_instance();
	mgr.add_component<Transform>(this->id, position, rotation, scale);
	mgr.add_component<Metadata>(this->id, name, tag);
}

void GameObject::set_parent(const GameObject & parent) {
	auto & mgr = ComponentManager::get_instance();

	// set parent on own Metadata component
	vector<reference_wrapper<Metadata>> this_metadata
		= mgr.get_components_by_id<Metadata>(this->id);
	this_metadata.at(0).get().parent = parent.id;

	// add own id to children list of parent's Metadata component
	vector<reference_wrapper<Metadata>> parent_metadata
		= mgr.get_components_by_id<Metadata>(parent.id);
	parent_metadata.at(0).get().children.push_back(this->id);
}
