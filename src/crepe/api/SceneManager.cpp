#include "../ComponentManager.h"

#include "SceneManager.h"

using namespace crepe;
using namespace std;

SceneManager::SceneManager() {}

SceneManager & SceneManager::get_instance() {
	static SceneManager instance;
	return instance;
}

// Set the next scene (this scene will be loaded at the end of the frame)
void SceneManager::set_next_scene(const std::string & name) {
	next_scene = name;
}

// Load a new scene (if there is one)
void SceneManager::load_next_scene() {
	if (!next_scene.empty()) {
		for (auto & scene : scenes) {
			if (scene->name == next_scene) {
				// Delete all components of the current scene
				ComponentManager & mgr = ComponentManager::get_instance();
				mgr.delete_all_components();
				// Load the new scene
				scene->load_scene();
				break;
			}
		}
	}
}
