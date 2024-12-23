#include <gtest/gtest.h>

#define protected public
#define private public

#include <crepe/api/GameObject.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <crepe/manager/ComponentManager.h>

using namespace std;
using namespace crepe;

class ECSTest : public ::testing::Test {
	Mediator m;

public:
	ComponentManager mgr {m};

	class TestComponent : public Component {
		using Component::Component;
	};
};

TEST_F(ECSTest, createGameObject) {
	GameObject obj = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 1);
	EXPECT_EQ(transform.size(), 1);

	EXPECT_EQ(metadata[0].get().name, "body");
	EXPECT_EQ(metadata[0].get().tag, "person");
	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[0].get().children.size(), 0);

	EXPECT_EQ(transform[0].get().position.x, 0);
	EXPECT_EQ(transform[0].get().position.y, 0);
	EXPECT_EQ(transform[0].get().rotation, 0);
	EXPECT_EQ(transform[0].get().scale, 1);
}

TEST_F(ECSTest, deleteAllGameObjects) {
	GameObject obj0 = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);

	mgr.delete_all_components();

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 0);
	EXPECT_EQ(transform.size(), 0);

	GameObject obj2 = mgr.new_object("body2", "person2", vec2 {1, 0}, 5, 1);

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 1);
	EXPECT_EQ(transform.size(), 1);

	EXPECT_EQ(metadata[0].get().game_object_id, 0);
	EXPECT_EQ(metadata[0].get().name, "body2");
	EXPECT_EQ(metadata[0].get().tag, "person2");
	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[0].get().children.size(), 0);

	EXPECT_EQ(transform[0].get().game_object_id, 0);
	EXPECT_EQ(transform[0].get().position.x, 1);
	EXPECT_EQ(transform[0].get().position.y, 0);
	EXPECT_EQ(transform[0].get().rotation, 5);
	EXPECT_EQ(transform[0].get().scale, 1);
}

TEST_F(ECSTest, deleteGameObject) {
	GameObject obj0 = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);

	mgr.delete_all_components_of_id(0);

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 1);
	EXPECT_EQ(transform.size(), 1);

	EXPECT_EQ(metadata[0].get().game_object_id, 1);
	EXPECT_EQ(metadata[0].get().name, "body");
	EXPECT_EQ(metadata[0].get().tag, "person");
	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[0].get().children.size(), 0);

	EXPECT_EQ(transform[0].get().game_object_id, 1);
	EXPECT_EQ(transform[0].get().position.x, 0);
	EXPECT_EQ(transform[0].get().position.y, 0);
	EXPECT_EQ(transform[0].get().rotation, 0);
	EXPECT_EQ(transform[0].get().scale, 1);
}

TEST_F(ECSTest, manyGameObjects) {
	for (int i = 0; i < 5000; i++) {
		GameObject obj = mgr.new_object("body", "person", vec2 {0, 0}, 0, i);
	}

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 5000);
	EXPECT_EQ(transform.size(), 5000);
	for (int i = 0; i < 5000; i++) {
		EXPECT_EQ(metadata[i].get().game_object_id, i);
		EXPECT_EQ(metadata[i].get().name, "body");
		EXPECT_EQ(metadata[i].get().tag, "person");
		EXPECT_EQ(metadata[i].get().parent, -1);
		EXPECT_EQ(metadata[i].get().children.size(), 0);

		EXPECT_EQ(transform[i].get().game_object_id, i);
		EXPECT_EQ(transform[i].get().position.x, 0);
		EXPECT_EQ(transform[i].get().position.y, 0);
		EXPECT_EQ(transform[i].get().rotation, 0);
		EXPECT_EQ(transform[i].get().scale, i);
	}

	mgr.delete_components<Metadata>();

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 0);
	EXPECT_EQ(transform.size(), 5000);

	for (int i = 0; i < 10000 - 5000; i++) {
		string tag = "person" + to_string(i);
		GameObject obj = mgr.new_object("body", tag, vec2 {0, 0}, i, 0);
	}

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 10000 - 5000);
	EXPECT_EQ(transform.size(), 10000);

	for (int i = 0; i < 10000 - 5000; i++) {
		EXPECT_EQ(metadata[i].get().game_object_id, i + 5000);
		EXPECT_EQ(metadata[i].get().name, "body");
		EXPECT_EQ(metadata[i].get().tag, "person" + to_string(i));
		EXPECT_EQ(metadata[i].get().parent, -1);
		EXPECT_EQ(metadata[i].get().children.size(), 0);

		EXPECT_EQ(transform[i].get().game_object_id, i);
		EXPECT_EQ(transform[i].get().position.x, 0);
		EXPECT_EQ(transform[i].get().position.y, 0);
		EXPECT_EQ(transform[i].get().rotation, 0);
		EXPECT_EQ(transform[i].get().scale, i);
	}

	mgr.delete_all_components();

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 0);
	EXPECT_EQ(transform.size(), 0);

	for (int i = 0; i < 10000; i++) {
		string name = "body" + to_string(i);
		GameObject obj = mgr.new_object(name, "person", vec2 {0, 0}, 0, 0);
	}

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 10000);
	EXPECT_EQ(transform.size(), 10000);

	for (int i = 0; i < 10000; i++) {
		EXPECT_EQ(metadata[i].get().game_object_id, i);
		EXPECT_EQ(metadata[i].get().name, "body" + to_string(i));
		EXPECT_EQ(metadata[i].get().tag, "person");
		EXPECT_EQ(metadata[i].get().parent, -1);
		EXPECT_EQ(metadata[i].get().children.size(), 0);

		EXPECT_EQ(transform[i].get().game_object_id, i);
		EXPECT_EQ(transform[i].get().position.x, 0);
		EXPECT_EQ(transform[i].get().position.y, 0);
		EXPECT_EQ(transform[i].get().rotation, 0);
		EXPECT_EQ(transform[i].get().scale, 0);
	}
}

TEST_F(ECSTest, getComponentsByID) {
	GameObject obj0 = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_id<Metadata>(0);
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_id<Transform>(1);

	EXPECT_EQ(metadata.size(), 1);
	EXPECT_EQ(transform.size(), 1);

	EXPECT_EQ(metadata[0].get().game_object_id, 0);
	EXPECT_EQ(metadata[0].get().name, "body");
	EXPECT_EQ(metadata[0].get().tag, "person");
	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[0].get().children.size(), 0);

	EXPECT_EQ(transform[0].get().game_object_id, 1);
	EXPECT_EQ(transform[0].get().position.x, 0);
	EXPECT_EQ(transform[0].get().position.y, 0);
	EXPECT_EQ(transform[0].get().rotation, 0);
	EXPECT_EQ(transform[0].get().scale, 1);
}

TEST_F(ECSTest, tooMuchComponents) {
	try {
		GameObject obj0 = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);
		obj0.add_component<Transform>(vec2 {10, 10}, 0, 1);
	} catch (const exception & e) {
		EXPECT_EQ(
			e.what(), string("Exceeded maximum number of instances for this component type")
		);
	}

	try {
		GameObject obj1 = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);
		obj1.add_component<Metadata>("body", "person");
	} catch (const exception & e) {
		EXPECT_EQ(
			e.what(), string("Exceeded maximum number of instances for this component type")
		);
	}

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();

	EXPECT_EQ(metadata.size(), 2);
	EXPECT_EQ(metadata[0].get().name, "body");
	EXPECT_EQ(metadata[1].get().name, "body");
}

TEST_F(ECSTest, partentChild) {
	{
		GameObject body = mgr.new_object("body", "person", vec2 {0, 0}, 0, 1);
		GameObject right_leg = mgr.new_object("rightLeg", "person", vec2 {1, 1}, 0, 1);
		GameObject left_leg = mgr.new_object("leftLeg", "person", vec2 {1, 1}, 0, 1);
		GameObject right_foot = mgr.new_object("rightFoot", "person", vec2 {2, 2}, 0, 1);
		GameObject left_foot = mgr.new_object("leftFoot", "person", vec2 {2, 2}, 0, 1);

		// Set the parent of each GameObject
		right_foot.set_parent(right_leg);
		left_foot.set_parent(left_leg);
		right_leg.set_parent(body);
		left_leg.set_parent(body);
	}

	// Get the Metadata and Transform components of each GameObject
	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();

	// Check IDs
	EXPECT_EQ(metadata[0].get().game_object_id, 0);
	EXPECT_EQ(metadata[1].get().game_object_id, 1);
	EXPECT_EQ(metadata[2].get().game_object_id, 2);
	EXPECT_EQ(metadata[3].get().game_object_id, 3);
	EXPECT_EQ(metadata[4].get().game_object_id, 4);

	// Check the parent-child relationships
	EXPECT_EQ(metadata[0].get().name, "body");
	EXPECT_EQ(metadata[1].get().name, "rightLeg");
	EXPECT_EQ(metadata[2].get().name, "leftLeg");
	EXPECT_EQ(metadata[3].get().name, "rightFoot");
	EXPECT_EQ(metadata[4].get().name, "leftFoot");

	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[1].get().parent, 0);
	EXPECT_EQ(metadata[2].get().parent, 0);
	EXPECT_EQ(metadata[3].get().parent, 1);
	EXPECT_EQ(metadata[4].get().parent, 2);

	EXPECT_EQ(metadata[0].get().children.size(), 2);
	EXPECT_EQ(metadata[1].get().children.size(), 1);
	EXPECT_EQ(metadata[2].get().children.size(), 1);
	EXPECT_EQ(metadata[3].get().children.size(), 0);
	EXPECT_EQ(metadata[4].get().children.size(), 0);

	EXPECT_EQ(metadata[0].get().children[0], 1);
	EXPECT_EQ(metadata[0].get().children[1], 2);
	EXPECT_EQ(metadata[1].get().children[0], 3);
	EXPECT_EQ(metadata[2].get().children[0], 4);
}

TEST_F(ECSTest, persistent) {
	GameObject obj0 = mgr.new_object("obj0", "obj0", vec2 {0, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("obj1", "obj1", vec2 {0, 0}, 0, 1);
	obj1.set_persistent();
	GameObject obj2 = mgr.new_object("obj2", "obj2", vec2 {0, 0}, 0, 1);

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 3);
	EXPECT_EQ(transform.size(), 3);

	mgr.delete_components_by_id<Metadata>(1);
	mgr.delete_components<Metadata>();
	mgr.delete_all_components_of_id(1);

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 1);
	EXPECT_EQ(transform.size(), 3);

	mgr.delete_all_components();

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 1);
	EXPECT_EQ(transform.size(), 1);

	EXPECT_EQ(metadata[0].get().game_object_id, 1);
	EXPECT_EQ(metadata[0].get().name, "obj1");
	EXPECT_EQ(metadata[0].get().tag, "obj1");
	EXPECT_EQ(metadata[0].get().parent, -1);
	EXPECT_EQ(metadata[0].get().children.size(), 0);

	EXPECT_EQ(transform[0].get().game_object_id, 1);
	EXPECT_EQ(transform[0].get().position.x, 0);
	EXPECT_EQ(transform[0].get().position.y, 0);

	GameObject obj3 = mgr.new_object("obj3", "obj3", vec2 {0, 0}, 0, 5);
	GameObject obj4 = mgr.new_object("obj4", "obj4", vec2 {0, 0}, 0, 5);

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 3);
	EXPECT_EQ(transform.size(), 3);

	EXPECT_EQ(metadata[0].get().game_object_id, 0);
	EXPECT_EQ(metadata[0].get().name, "obj3");

	EXPECT_EQ(metadata[1].get().game_object_id, 1);
	EXPECT_EQ(metadata[1].get().name, "obj1");

	EXPECT_EQ(metadata[2].get().game_object_id, 2);
	EXPECT_EQ(metadata[2].get().name, "obj4");

	EXPECT_EQ(transform[0].get().game_object_id, 0);
	EXPECT_EQ(transform[0].get().scale, 5);

	EXPECT_EQ(transform[1].get().game_object_id, 1);
	EXPECT_EQ(transform[1].get().scale, 1);

	EXPECT_EQ(transform[2].get().game_object_id, 2);
	EXPECT_EQ(transform[2].get().scale, 5);
}

TEST_F(ECSTest, resetPersistent) {
	GameObject obj0 = mgr.new_object("obj0", "obj0", vec2 {0, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("obj1", "obj1", vec2 {0, 0}, 0, 1);
	obj1.set_persistent();
	GameObject obj2 = mgr.new_object("obj2", "obj2", vec2 {0, 0}, 0, 1);

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 3);
	EXPECT_EQ(transform.size(), 3);

	mgr.delete_all_components();

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 1);
	EXPECT_EQ(transform.size(), 1);

	vector<reference_wrapper<Metadata>> metadata_id = mgr.get_components_by_id<Metadata>(1);

	EXPECT_EQ(metadata_id.size(), 1);
	EXPECT_EQ(metadata_id[0].get().game_object_id, 1);
	EXPECT_EQ(metadata_id[0].get().name, "obj1");

	mgr.set_persistent(1, false);
	mgr.delete_all_components();

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 0);
	EXPECT_EQ(transform.size(), 0);
}

TEST_F(ECSTest, IDByName) {
	GameObject foo = mgr.new_object("foo");
	GameObject bar = mgr.new_object("bar");

	{
		auto objects = mgr.get_objects_by_name("");
		EXPECT_EQ(objects.size(), 0);
	}

	{
		auto objects = mgr.get_objects_by_name("foo");
		EXPECT_EQ(objects.size(), 1);
		EXPECT_TRUE(objects.contains(foo.id));
	}
}

TEST_F(ECSTest, IDByTag) {
	GameObject foo = mgr.new_object("foo", "common tag");
	GameObject bar = mgr.new_object("bar", "common tag");

	{
		auto objects = mgr.get_objects_by_tag("");
		EXPECT_EQ(objects.size(), 0);
	}

	{
		auto objects = mgr.get_objects_by_tag("common tag");
		EXPECT_EQ(objects.size(), 2);
		EXPECT_TRUE(objects.contains(foo.id));
		EXPECT_TRUE(objects.contains(bar.id));
	}
}

TEST_F(ECSTest, ComponentsByName) {
	GameObject foo = mgr.new_object("foo");
	foo.add_component<TestComponent>();
	GameObject bar = mgr.new_object("bar");
	bar.add_component<TestComponent>();
	bar.add_component<TestComponent>();

	{
		auto objects = mgr.get_components_by_name<TestComponent>("");
		EXPECT_EQ(objects.size(), 0);
	}

	{
		auto objects = mgr.get_components_by_name<TestComponent>("foo");
		EXPECT_EQ(objects.size(), 1);
	}

	{
		auto objects = mgr.get_components_by_name<TestComponent>("bar");
		EXPECT_EQ(objects.size(), 2);
	}
}

TEST_F(ECSTest, ComponentsByTag) {
	GameObject foo = mgr.new_object("foo", "common tag");
	foo.add_component<TestComponent>();
	GameObject bar = mgr.new_object("bar", "common tag");
	bar.add_component<TestComponent>();
	bar.add_component<TestComponent>();

	{
		auto objects = mgr.get_components_by_tag<TestComponent>("");
		EXPECT_EQ(objects.size(), 0);
	}

	{
		auto objects = mgr.get_components_by_tag<TestComponent>("common tag");
		EXPECT_EQ(objects.size(), 3);
	}
}

TEST_F(ECSTest, Snapshot) {
	GameObject foo = mgr.new_object("foo");

	foo.transform.position = {1, 1};

	ComponentManager::Snapshot snapshot = mgr.save();

	foo.transform.position = {0, 0};

	mgr.restore(snapshot);

	EXPECT_EQ(foo.transform.position, (vec2 {1, 1}));
}
