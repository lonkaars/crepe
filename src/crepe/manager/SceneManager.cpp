#include <algorithm>
#include <memory>

#include "ComponentManager.h"
#include "SceneManager.h"

#include "util/Log.h"

using namespace crepe;
using namespace std;

SceneManager::SceneManager(Mediator & mediator) : Manager(mediator) {
	dbg_trace();
	mediator.scene_manager = *this;
}

void SceneManager::set_next_scene(const string & name) { next_scene = name; }

void SceneManager::load_next_scene() {
	// next scene not set
	if (this->next_scene.empty()) return;

	auto it = find_if(this->scenes.begin(), this->scenes.end(),
					  [&next_scene = this->next_scene](unique_ptr<Scene> & scene) {
						  return scene.get()->get_name() == next_scene;
					  });

	// next scene not found
	if (it == this->scenes.end()) return;
	unique_ptr<Scene> & scene = *it;

	// Delete all components of the current scene
	ComponentManager & mgr = this->mediator.component_manager;
	mgr.delete_all_components();

	// Load the new scene
	scene->load_scene();
}
