#include <gtest/gtest.h>

#define protected public

#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>

using namespace std;
using namespace crepe;

class ECSTest : public ::testing::Test {
public:
	ComponentManager mgr{};
};

TEST_F(ECSTest, createGameObject) {
	GameObject obj = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);

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
	GameObject obj0 = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);

	mgr.delete_all_components();

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 0);
	EXPECT_EQ(transform.size(), 0);

	GameObject obj2 = mgr.new_object("body2", "person2", vec2{1, 0}, 5, 1);

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
	GameObject obj0 = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);

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
		GameObject obj = mgr.new_object("body", "person", vec2{0, 0}, 0, i);
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
		GameObject obj = mgr.new_object("body", tag, vec2{0, 0}, i, 0);
	}

	metadata = mgr.get_components_by_type<Metadata>();
	transform = mgr.get_components_by_type<Transform>();

	EXPECT_EQ(metadata.size(), 10000 - 5000);
	EXPECT_EQ(transform.size(), 10000);
}

TEST_F(ECSTest, getComponentsByID) {
	GameObject obj0 = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
	GameObject obj1 = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);

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
		GameObject obj0 = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
		obj0.add_component<Transform>(vec2{10, 10}, 0, 1);
	} catch (const exception & e) {
		EXPECT_EQ(e.what(),
				  string("Exceeded maximum number of instances for this component type"));
	}

	try {
		GameObject obj1 = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
		obj1.add_component<Metadata>("body", "person");
	} catch (const exception & e) {
		EXPECT_EQ(e.what(),
				  string("Exceeded maximum number of instances for this component type"));
	}

	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();

	EXPECT_EQ(metadata.size(), 2);
	EXPECT_EQ(metadata[0].get().name, "body");
	EXPECT_EQ(metadata[1].get().name, "body");
}

TEST_F(ECSTest, partentChild) {
	{
		GameObject body = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
		GameObject right_leg
			= mgr.new_object("rightLeg", "person", vec2{1, 1}, 0, 1);
		GameObject left_leg = mgr.new_object("leftLeg", "person", vec2{1, 1}, 0, 1);
		GameObject right_foot
			= mgr.new_object("rightFoot", "person", vec2{2, 2}, 0, 1);
		GameObject left_foot
			= mgr.new_object("leftFoot", "person", vec2{2, 2}, 0, 1);

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
