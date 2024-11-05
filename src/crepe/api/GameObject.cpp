#include "api/Transform.h"

#include "Metadata.h"
#include "GameObject.h"

using namespace crepe::api;
using namespace std;

GameObject::GameObject(uint32_t id, std::string name, std::string tag, Point position, double rotation, double scale) : id(id) {
	ComponentManager & mgr = ComponentManager::get_instance();
	mgr.add_component<Transform>(this->id, position, rotation, scale);
	mgr.add_component<Metadata>(this->id, name, tag);
}

void GameObject::set_parent(GameObject & parent) {
	auto & mgr = ComponentManager::get_instance();
	vector<reference_wrapper<Metadata>> thisMetadata = mgr.get_components_by_id<Metadata>(this->id);
	vector<reference_wrapper<Metadata>> parentMetadata = mgr.get_components_by_id<Metadata>(parent.id);
	thisMetadata.at(0).get().parent = parent.id;
	parentMetadata.at(0).get().children.push_back(this->id);
}
