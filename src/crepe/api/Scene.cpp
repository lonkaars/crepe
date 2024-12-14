#include "Scene.h"

using namespace crepe;

SaveManager & Scene::get_save_manager() const { return mediator->save_manager; }

GameObject Scene::new_object(const std::string & name, const std::string & tag,
							 const vec2 & position, double rotation, double scale) {
	// Forward the call to ComponentManager's new_object method
	return mediator->component_manager->new_object(name, tag, position, rotation, scale);
}

void Scene::set_persistent(const Asset & asset, bool persistent) {
	mediator->resource_manager->set_persistent(asset, persistent);
}
