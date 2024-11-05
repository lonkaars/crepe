#include "../ComponentManager.h"

#include "SceneManager.h"

using namespace crepe;

SceneManager::SceneManager() {}

SceneManager & SceneManager::get_instance() {
	static SceneManager instance;
	return instance;
}

// Push the next scene onto the queue
void SceneManager::load_scene(std::string name) { next_scene.push(name); }

// Load a new scene from the queue (if there is one)
void SceneManager::empty_queue() {
	while (!next_scene.empty()) {
		string name = next_scene.front();
		next_scene.pop();

		for (auto & scene : scenes) {
			if (scene->name == name) {
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
