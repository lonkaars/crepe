#include "system/ScriptSystem.h"
#include "types.h"
#include <gtest/gtest.h>

#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Event.h>
#include <crepe/api/EventManager.h>
#include <crepe/api/Script.h>

#include <crepe/ComponentManager.h>
#include <crepe/system/CollisionSystem.h>
#include "iostream"

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

//scripts for object 1 collision test
class UnitTestBoxBoxCollision1 : public Script {
	static bool oncollision(const CollisionEvent& test) {
		std::cout << "collision event 1" << std::endl;
		return true;
	}
	void init() {
		EventManager::get_instance().subscribe<CollisionEvent>(oncollision, this->get_game_object_id());
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
		
	}
};

//scripts for object 1 collision test
class UnitTestBoxBoxCollision2 : public Script {
	static bool oncollision(const CollisionEvent& test) {
		std::cout << "collision event 1" << std::endl;
		return true;
	}
	void init() {
		EventManager::get_instance().subscribe<CollisionEvent>(oncollision, this->get_game_object_id());
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
		
	}
};

class CollisionTest : public ::testing::Test {
public:
	ComponentManager component_manager;
	CollisionSystem system{component_manager};
	ScriptSystem sr{component_manager};
	const double screen_size_width = 640;
	const double screen_size_height = 480;
	const double world_collider = 1000;
	
	void SetUp() override {
		ComponentManager & mgr = this->component_manager;
		if(mgr.get_components_by_id<Transform>(0).empty())
		{
			create_test_world();
			create_test_components();
		}
		reset_test_components();
		sr.update();
	}

	void create_test_world() {
		
		ComponentManager & mgr = this->component_manager;
		GameObject world = mgr.new_object("Name", "Tag", Vector2{screen_size_width/2, screen_size_height/2}, 0, 1);
		world.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 0,
			.gravity_scale = 0,
			.body_type = Rigidbody::BodyType::STATIC,
			.constraints = {0, 0, 0},
			.use_gravity = false,
			.bounce = false,
			.offset = {0,0}
		});
		world.add_component<BoxCollider>(Vector2{0, 0-(screen_size_height/2+world_collider/2)}, world_collider, world_collider);;	// Top
		world.add_component<BoxCollider>(Vector2{0, screen_size_height/2+world_collider/2}, world_collider, world_collider); // Bottom
		world.add_component<BoxCollider>(Vector2{0-(screen_size_width/2+world_collider/2), 0}, world_collider, world_collider); // Left
		world.add_component<BoxCollider>(Vector2{screen_size_width/2+world_collider/2, 0}, world_collider, world_collider); // right
	}

	void create_test_components()
	{
		ComponentManager & mgr = this->component_manager;
		GameObject game_object1 = mgr.new_object("Name", "Tag", Vector2{screen_size_width/2, screen_size_height/2}, 0, 1);
		game_object1.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 1,
		.gravity_scale = 0.01,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = {1,0},
		.constraints = {0, 0, 0},
		.use_gravity = true,
		.bounce = true,
		.elastisity = 1,
		.offset = {0,0},
		});
		game_object1.add_component<BoxCollider>(Vector2{0, 0}, 20, 20);
		game_object1.add_component<BehaviorScript>().set_script<UnitTestBoxBoxCollision1>();

		
		GameObject game_object2 = mgr.new_object("Name", "Tag", Vector2{screen_size_width/2, screen_size_height/2-100}, 0, 1);
		game_object2.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 1,
		.gravity_scale = 0.01,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = {1,0},
		.constraints = {0, 0, 0},
		.use_gravity = true,
		.bounce = true,
		.elastisity = 1,
		.offset = {0,0},
		});
		game_object2.add_component<BoxCollider>(Vector2{0, 0}, 20, 20);
		game_object2.add_component<BehaviorScript>().set_script<UnitTestBoxBoxCollision2>();
	}

	void reset_test_components()
	{
		ComponentManager & mgr = this->component_manager;
		//game object 1
		{
			game_object_id_t id = 1;
			Transform & tf = mgr.get_components_by_id<Transform>(id).front().get();
			tf.position = Vector2{screen_size_width/2, screen_size_height/2};
			tf.rotation = 0;
			tf.scale = 1;
			tf.active = 1;
			Rigidbody & rg = mgr.get_components_by_id<Rigidbody>(id).front().get();
			rg.data.angular_damping = 0;
			rg.data.angular_velocity = 0;
			rg.data.max_angular_velocity = 100;
			rg.data.linear_velocity = {0,0};
			rg.data.linear_damping = {0,0};
			rg.data.max_linear_velocity = {100,100};
			rg.data.bounce = false;
			rg.data.elastisity = 0;
			rg.data.offset = {0,0};
			rg.data.constraints = {0,0,0};
		}

		{
			game_object_id_t id = 2;
			Transform & tf = mgr.get_components_by_id<Transform>(id).front().get();
			tf.position = Vector2{screen_size_width/2, screen_size_height/2-100};
			tf.rotation = 0;
			tf.scale = 1;
			tf.active = 1;
			Rigidbody & rg = mgr.get_components_by_id<Rigidbody>(id).front().get();
			rg.data.angular_damping = 0;
			rg.data.angular_velocity = 0;
			rg.data.max_angular_velocity = 100;
			rg.data.linear_velocity = {0,0};
			rg.data.linear_damping = {0,0};
			rg.data.max_linear_velocity = {100,100};
			rg.data.bounce = false;
			rg.data.elastisity = 0;
			rg.data.offset = {0,0};
			rg.data.constraints = {0,0,0};
		}
	}
};

TEST_F(CollisionTest, collision_example) {
	// change object data before calling update

	// call collision system update
	system.update();
	// should be nullptr after update with no collision
	//ASSERT_EQ(MyScriptCollider1::last_collision_info_1, nullptr);
	//ASSERT_EQ(MyScriptCollider2::last_collision_info_2, nullptr);
	// check if values are correct (filled in data)
	// EXPECT_EQ(MyScriptCollider1::last_collision_info->first.collider.game_object_id, 1);
	// EXPECT_EQ(MyScriptCollider2::last_collision_info->second.collider.game_object_id, 2);
	// check test data
}

TEST_F(CollisionTest, collision_box_box_dynamic) {
	// change object data before calling update
	ComponentManager & mgr = this->component_manager;
	Transform & test = mgr.get_components_by_id<Transform>(2).front().get();
	test.position = {screen_size_width/2,screen_size_height/2};
	// call collision system update
	system.update();
	// should be nullptr after update with no collision
	// ASSERT_NE(MyScriptCollider1::last_collision_info_1, nullptr);
	// ASSERT_NE(MyScriptCollider2::last_collision_info_2, nullptr);
	// // check if values are correct (filled in data)
	// EXPECT_EQ(MyScriptCollider1::last_collision_info_1->first.collider.game_object_id, 1);
	// EXPECT_EQ(MyScriptCollider2::last_collision_info_2->second.collider.game_object_id, 2);
	// check test data
}
