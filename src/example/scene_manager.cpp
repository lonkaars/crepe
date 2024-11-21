#include <iostream>

#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Scene.h>
#include <crepe/api/SceneManager.h>
#include <crepe/api/Vector2.h>

using namespace crepe;
using namespace std;

class ConcreteScene1 : public Scene {
public:
	using Scene::Scene;

	void load_scene() {
		auto & mgr = this->component_manager;
		GameObject object1 = mgr.new_object("scene_1", "tag_scene_1", Vector2{0, 0}, 0, 1);
		GameObject object2 = mgr.new_object("scene_1", "tag_scene_1", Vector2{1, 0}, 0, 1);
		GameObject object3 = mgr.new_object("scene_1", "tag_scene_1", Vector2{2, 0}, 0, 1);
	}

	string get_name() { return "scene1"; }
};

class ConcreteScene2 : public Scene {
public:
	using Scene::Scene;

	void load_scene() {
		auto & mgr = this->component_manager;
		GameObject object1 = mgr.new_object("scene_2", "tag_scene_2", Vector2{0, 0}, 0, 1);
		GameObject object2 = mgr.new_object("scene_2", "tag_scene_2", Vector2{0, 1}, 0, 1);
		GameObject object3 = mgr.new_object("scene_2", "tag_scene_2", Vector2{0, 2}, 0, 1);
		GameObject object4 = mgr.new_object("scene_2", "tag_scene_2", Vector2{0, 3}, 0, 1);
	}

	string get_name() { return "scene2"; }
};

int main() {
	ComponentManager component_mgr{};
	SceneManager scene_mgr{component_mgr};

	// Add the scenes to the scene manager
	scene_mgr.add_scene<ConcreteScene1>();
	scene_mgr.add_scene<ConcreteScene2>();

	// There is no need to call set_next_scene() at the beginnen, because the first scene will be
	// automatically set as the next scene

	// Load scene1 (the first scene added)
	scene_mgr.load_next_scene();

	// Get the Metadata components of each GameObject of Scene1
	vector<reference_wrapper<Metadata>> metadata
		= component_mgr.get_components_by_type<Metadata>();

	cout << "Metadata components of Scene1:" << endl;
	// Print the Metadata
	for (auto & m : metadata) {
		cout << "Id: " << m.get().game_object_id << " Name: " << m.get().name
			 << " Tag: " << m.get().tag << endl;
	}

	// Set scene2 as the next scene
	scene_mgr.set_next_scene("scene2");
	// Load scene2
	scene_mgr.load_next_scene();

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
