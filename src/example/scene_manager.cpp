#include <iostream>

#include "../crepe/api/SceneManager.h"
#include "../crepe/api/Scene.h"
#include "../crepe/api/GameObject.h"
#include "../crepe/Metadata.h"
#include "../crepe/ComponentManager.h"

using namespace crepe::api;
using namespace crepe;
using namespace std;

class concreteScene1 : public Scene {
public:
	concreteScene1(string name) : Scene(name) {}

	void load_scene() {
		GameObject object1(0, "scene_1", "tag_scene_1", Point{0, 0}, 0, 1);
		GameObject object2(1, "scene_1", "tag_scene_1", Point{1, 0}, 0, 1);
		GameObject object3(2, "scene_1", "tag_scene_1", Point{2, 0}, 0, 1);
	}
};

class concreteScene2 : public Scene {
public:
	concreteScene2(string name) : Scene(name) {}

	void load_scene() {
		GameObject object1(0, "scene_2", "tag_scene_2", Point{0, 0}, 0, 1);
		GameObject object2(1, "scene_2", "tag_scene_2", Point{0, 1}, 0, 1);
		GameObject object3(2, "scene_2", "tag_scene_2", Point{0, 2}, 0, 1);
		GameObject object4(3, "scene_2", "tag_scene_2", Point{0, 3}, 0, 1);
	}
};

int main() {
	SceneManager & scene_mgr = SceneManager::get_instance();

	// Add the scenes to the scene manager
	scene_mgr.add_scene<concreteScene1>("scene1");
	scene_mgr.add_scene<concreteScene2>("scene2");

	// Load scene1 to the queue
	scene_mgr.load_scene("scene1");
	// Empty the queue (now scene1 is loaded)
	scene_mgr.empty_queue();

	// Get the Metadata components of each GameObject of Scene1
	ComponentManager & component_mgr = ComponentManager::get_instance();
	vector<reference_wrapper<Metadata>> metadata = component_mgr.get_components_by_type<Metadata>();
	
	cout << "Metadata components of Scene1:" << endl;
	// Print the Metadata
	for (auto & m : metadata) {
		cout << "Id: " << m.get().game_object_id << " Name: " << m.get().name
			 << " Tag: " << m.get().tag << endl;
	}

	// Load scene2 to the queue
	scene_mgr.load_scene("scene2");
	// Empty the queue (now scene2 is loaded)
	scene_mgr.empty_queue();

	// Get the Metadata components of each GameObject of Scene2
	metadata = component_mgr.get_components_by_type<Metadata>();
	
	cout << "Metadata components of Scene2:" << endl;
	// Print the Metadata
	for (auto & m : metadata) {
		cout << "Id: " << m.get().game_object_id << " Name: " << m.get().name
			 << " Tag: " << m.get().tag << endl;
	}

	return 0;
}
