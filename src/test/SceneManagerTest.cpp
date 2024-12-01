#include "types.h"
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Scene.h>
#include <crepe/api/SceneManager.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <gtest/gtest.h>

using namespace std;
using namespace crepe;

class ConcreteScene1 : public Scene {
public:
	void load_scene() {
		ComponentManager & mgr = this->component_manager;
		GameObject object1 = mgr.new_object("scene_1", "tag_scene_1", vec2{0, 0}, 0, 1);
		GameObject object2 = mgr.new_object("scene_1", "tag_scene_1", vec2{1, 0}, 0, 1);
		GameObject object3 = mgr.new_object("scene_1", "tag_scene_1", vec2{2, 0}, 0, 1);
	}

	string get_name() const { return "scene1"; }
};

class ConcreteScene2 : public Scene {
public:
	void load_scene() {
		ComponentManager & mgr = this->component_manager;
		GameObject object1 = mgr.new_object("scene_2", "tag_scene_2", vec2{0, 0}, 0, 1);
		GameObject object2 = mgr.new_object("scene_2", "tag_scene_2", vec2{0, 1}, 0, 1);
		GameObject object3 = mgr.new_object("scene_2", "tag_scene_2", vec2{0, 2}, 0, 1);
		GameObject object4 = mgr.new_object("scene_2", "tag_scene_2", vec2{0, 3}, 0, 1);
	}

	string get_name() const { return "scene2"; }
};

class ConcreteScene3 : public Scene {
public:
	ConcreteScene3(const string & name) : name(name) {}

	void load_scene() {
		ComponentManager & mgr = this->component_manager;
		GameObject object1 = mgr.new_object("scene_3", "tag_scene_3", vec2{0, 0}, 0, 1);
	}

	string get_name() const { return name; }

private:
	const string name;
};

class SceneManagerTest : public ::testing::Test {
public:
	ComponentManager component_mgr{};
	SceneManager scene_mgr{component_mgr};
};

TEST_F(SceneManagerTest, loadScene) {
	scene_mgr.add_scene<ConcreteScene1>();
	scene_mgr.add_scene<ConcreteScene2>();

	scene_mgr.load_next_scene();

	vector<reference_wrapper<Metadata>> metadata
		= component_mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform
		= component_mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 3);
	EXPECT_EQ(transform.size(), 3);

	EXPECT_EQ(metadata[0].get().game_object_id, 0);
	EXPECT_EQ(metadata[0].get().name, "scene_1");
	EXPECT_EQ(metadata[0].get().tag, "tag_scene_1");
	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[0].get().children.size(), 0);
	EXPECT_EQ(transform[0].get().position.x, 0);
	EXPECT_EQ(transform[0].get().position.y, 0);

	EXPECT_EQ(metadata[1].get().game_object_id, 1);
	EXPECT_EQ(metadata[1].get().name, "scene_1");
	EXPECT_EQ(metadata[1].get().tag, "tag_scene_1");
	EXPECT_EQ(metadata[1].get().parent, -1);
	EXPECT_EQ(metadata[1].get().children.size(), 0);
	EXPECT_EQ(transform[1].get().position.x, 1);
	EXPECT_EQ(transform[1].get().position.y, 0);

	EXPECT_EQ(metadata[2].get().game_object_id, 2);
	EXPECT_EQ(metadata[2].get().name, "scene_1");
	EXPECT_EQ(metadata[2].get().tag, "tag_scene_1");
	EXPECT_EQ(metadata[2].get().parent, -1);
	EXPECT_EQ(metadata[2].get().children.size(), 0);
	EXPECT_EQ(transform[2].get().position.x, 2);
	EXPECT_EQ(transform[2].get().position.y, 0);

	scene_mgr.set_next_scene("scene2");
	scene_mgr.load_next_scene();

	metadata = component_mgr.get_components_by_type<Metadata>();
	transform = component_mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 4);
	EXPECT_EQ(transform.size(), 4);

	EXPECT_EQ(metadata[0].get().game_object_id, 0);
	EXPECT_EQ(metadata[0].get().name, "scene_2");
	EXPECT_EQ(metadata[0].get().tag, "tag_scene_2");
	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[0].get().children.size(), 0);
	EXPECT_EQ(transform[0].get().position.x, 0);
	EXPECT_EQ(transform[0].get().position.y, 0);

	EXPECT_EQ(metadata[1].get().game_object_id, 1);
	EXPECT_EQ(metadata[1].get().name, "scene_2");
	EXPECT_EQ(metadata[1].get().tag, "tag_scene_2");
	EXPECT_EQ(metadata[1].get().parent, -1);
	EXPECT_EQ(metadata[1].get().children.size(), 0);
	EXPECT_EQ(transform[1].get().position.x, 0);
	EXPECT_EQ(transform[1].get().position.y, 1);

	EXPECT_EQ(metadata[2].get().game_object_id, 2);
	EXPECT_EQ(metadata[2].get().name, "scene_2");
	EXPECT_EQ(metadata[2].get().tag, "tag_scene_2");
	EXPECT_EQ(metadata[2].get().parent, -1);
	EXPECT_EQ(metadata[2].get().children.size(), 0);
	EXPECT_EQ(transform[2].get().position.x, 0);
	EXPECT_EQ(transform[2].get().position.y, 2);

	EXPECT_EQ(metadata[3].get().game_object_id, 3);
	EXPECT_EQ(metadata[3].get().name, "scene_2");
	EXPECT_EQ(metadata[3].get().tag, "tag_scene_2");
	EXPECT_EQ(metadata[3].get().parent, -1);
	EXPECT_EQ(metadata[3].get().children.size(), 0);
	EXPECT_EQ(transform[3].get().position.x, 0);
	EXPECT_EQ(transform[3].get().position.y, 3);
}

TEST_F(SceneManagerTest, perfectForwarding) {
	scene_mgr.add_scene<ConcreteScene3>("scene3");

	scene_mgr.load_next_scene();

	vector<reference_wrapper<Metadata>> metadata
		= component_mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform
		= component_mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 1);
	EXPECT_EQ(transform.size(), 1);

	EXPECT_EQ(metadata[0].get().game_object_id, 0);
	EXPECT_EQ(metadata[0].get().name, "scene_3");
	EXPECT_EQ(metadata[0].get().tag, "tag_scene_3");
	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[0].get().children.size(), 0);
	EXPECT_EQ(transform[0].get().position.x, 0);
	EXPECT_EQ(transform[0].get().position.y, 0);
}
