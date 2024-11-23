#include <cmath>
#include <cstddef>
#include <gtest/gtest.h>

#define private public
#define protected public

#include <crepe/ComponentManager.h>
#include <crepe/api/Event.h>
#include <crepe/api/EventManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Transform.h>
#include <crepe/system/CollisionSystem.h>
#include <crepe/system/ScriptSystem.h>
#include <crepe/types.h>
#include <crepe/util/Log.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;
using namespace testing;

// class MyScript : public Script {
// 	bool oncollision(const CollisionEvent& test) {
// 		Log::logf("Box {} script on_collision()", test.info.first.collider.game_object_id);
// 		return true;
// 	}
// 	void init() {
// 		subscribe<CollisionEvent>([this](const CollisionEvent& ev) -> bool {
// 			return this->oncollision(ev);
// 		});
// 	}
// 	void update() {
// 		// Retrieve component from the same GameObject this script is on
// 	}
// };


class CollisionHandler : public Script {
public:
	int box_id;
	function<void(const CollisionEvent& ev)> test_fn = [](const CollisionEvent & ev) { };

	CollisionHandler(int box_id) {
		this->box_id = box_id;
	}

	bool on_collision(const CollisionEvent& ev) {
		//Log::logf("Box {} script on_collision()", box_id);
		test_fn(ev);
		return true;
	}

	void init() {
		subscribe<CollisionEvent>([this](const CollisionEvent& ev) -> bool {
			return this->on_collision(ev);
		});
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
	}
};

class CollisionTest : public Test {
public:
	ComponentManager mgr;
	CollisionSystem collision_sys{mgr};
	ScriptSystem script_sys{mgr};

	GameObject world = mgr.new_object("world","",{50,50});
	GameObject game_object1 = mgr.new_object("object1", "", { 50, 50});
	GameObject game_object2 = mgr.new_object("object2", "", { 50, 30});

	CollisionHandler * script_object1_ref = nullptr;
	CollisionHandler * script_object2_ref = nullptr;
	
	void SetUp() override {
		world.add_component<Rigidbody>(Rigidbody::Data{
			// TODO: remove unrelated properties:
			.body_type = Rigidbody::BodyType::STATIC,
			.bounce = false,
			.offset = {0,0},
		});
		// Create a box with an inner size of 10x10 units
		world.add_component<BoxCollider>(vec2{0, -100}, 100, 100); // Top
		world.add_component<BoxCollider>(vec2{0, 100}, 100, 100); // Bottom
		world.add_component<BoxCollider>(vec2{-100, 0}, 100, 100); // Left
		world.add_component<BoxCollider>(vec2{100, 0}, 100, 100); // right

		game_object1.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 0.01,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.linear_velocity = {0,0},
			.constraints = {0, 0, 0},
			.use_gravity = true,
			.bounce = true,
			.elastisity = 1,
			.offset = {0,0},
		});
		game_object1.add_component<BoxCollider>(vec2{0, 0}, 10, 10);
		BehaviorScript & script_object1 = game_object1.add_component<BehaviorScript>().set_script<CollisionHandler>(1);
		script_object1_ref = static_cast<CollisionHandler*>(script_object1.script.get());
		ASSERT_NE(script_object1_ref, nullptr);
		
		game_object2.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 0.01,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.linear_velocity = {0,0},
			.constraints = {0, 0, 0},
			.use_gravity = true,
			.bounce = true,
			.elastisity = 1,
			.offset = {0,0},
		});
		game_object2.add_component<BoxCollider>(vec2{0, 0}, 10, 10);
		BehaviorScript & script_object2 = game_object2.add_component<BehaviorScript>().set_script<CollisionHandler>(2);
		script_object2_ref = static_cast<CollisionHandler*>(script_object2.script.get());
		ASSERT_NE(script_object2_ref, nullptr);

		// Ensure Script::init() is called on all BehaviorScript instances
		script_sys.update();
	}
};

TEST_F(CollisionTest, collision_example) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 2);
	};
	EXPECT_FALSE(collision_happend);
	collision_sys.update();
	EXPECT_FALSE(collision_happend);
}

TEST_F(CollisionTest, collision_box_box_dynamic_both_no_velocity) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, 10);
		EXPECT_EQ(ev.info.move_back_value.y, 10);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::BOTH);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 2);
		EXPECT_EQ(ev.info.move_back_value.x, 10);
		EXPECT_EQ(ev.info.move_back_value.y, 10);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::BOTH);
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {50,30};
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}

TEST_F(CollisionTest, collision_box_box_dynamic_x_direction_no_velocity) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, -5);
		EXPECT_EQ(ev.info.move_back_value.y, 0);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::X_DIRECTION);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 2);
		EXPECT_EQ(ev.info.move_back_value.x, 5);
		EXPECT_EQ(ev.info.move_back_value.y, 0);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::X_DIRECTION);
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {45,30};
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}

TEST_F(CollisionTest, collision_box_box_dynamic_y_direction_no_velocity) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, 0);
		EXPECT_EQ(ev.info.move_back_value.y, -5);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::Y_DIRECTION);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 2);
		EXPECT_EQ(ev.info.move_back_value.x, 0);
		EXPECT_EQ(ev.info.move_back_value.y, 5);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::Y_DIRECTION);
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {50,25};
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}

TEST_F(CollisionTest, collision_box_box_dynamic_both) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, 10);
		EXPECT_EQ(ev.info.move_back_value.y, 10);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::BOTH);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 2);
		EXPECT_EQ(ev.info.move_back_value.x, 10);
		EXPECT_EQ(ev.info.move_back_value.y, 10);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::BOTH);
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {50,30};
	Rigidbody & rg1 = this->mgr.get_components_by_id<Rigidbody>(1).front().get();
	rg1.data.linear_velocity = {10,10};
	Rigidbody & rg2 = this->mgr.get_components_by_id<Rigidbody>(2).front().get();
	rg2.data.linear_velocity = {10,10};
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}

TEST_F(CollisionTest, collision_box_box_dynamic_x_direction) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, -5);
		EXPECT_EQ(ev.info.move_back_value.y, -5);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::X_DIRECTION);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 2);
		EXPECT_EQ(ev.info.move_back_value.x, 5);
		EXPECT_EQ(ev.info.move_back_value.y, 5);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::X_DIRECTION);
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {45,30};
	Rigidbody & rg1 = this->mgr.get_components_by_id<Rigidbody>(1).front().get();
	rg1.data.linear_velocity = {10,10};
	Rigidbody & rg2 = this->mgr.get_components_by_id<Rigidbody>(2).front().get();
	rg2.data.linear_velocity = {10,10};
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}

TEST_F(CollisionTest, collision_box_box_dynamic_y_direction) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, -5);
		EXPECT_EQ(ev.info.move_back_value.y, -5);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::Y_DIRECTION);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 2);
		EXPECT_EQ(ev.info.move_back_value.x, 5);
		EXPECT_EQ(ev.info.move_back_value.y, 5);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::Y_DIRECTION);
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {50,25};
	Rigidbody & rg1 = this->mgr.get_components_by_id<Rigidbody>(1).front().get();
	rg1.data.linear_velocity = {10,10};
	Rigidbody & rg2 = this->mgr.get_components_by_id<Rigidbody>(2).front().get();
	rg2.data.linear_velocity = {10,10};
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}


TEST_F(CollisionTest, collision_box_box_static_both) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, 10);
		EXPECT_EQ(ev.info.move_back_value.y, 10);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::BOTH);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		// is static should not be called
		FAIL();
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {50,30};
	Rigidbody & rg2 = this->mgr.get_components_by_id<Rigidbody>(2).front().get();
	rg2.data.body_type = crepe::Rigidbody::BodyType::STATIC;
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}

TEST_F(CollisionTest, collision_box_box_static_x_direction) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, -5);
		EXPECT_EQ(ev.info.move_back_value.y, -5);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::X_DIRECTION);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		// is static should not be called
		FAIL();
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {45,30};
	Rigidbody & rg1 = this->mgr.get_components_by_id<Rigidbody>(1).front().get();
	rg1.data.linear_velocity = {10,10};
	Rigidbody & rg2 = this->mgr.get_components_by_id<Rigidbody>(2).front().get();
	rg2.data.body_type = crepe::Rigidbody::BodyType::STATIC;
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}

TEST_F(CollisionTest, collision_box_box_static_y_direction) {
	bool collision_happend = false;
	script_object1_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		collision_happend = true;
		EXPECT_EQ(ev.info.first.collider.game_object_id, 1);
		EXPECT_EQ(ev.info.move_back_value.x, -5);
		EXPECT_EQ(ev.info.move_back_value.y, -5);
		EXPECT_EQ(ev.info.move_back_direction, crepe::CollisionSystem::Direction::Y_DIRECTION);
	};
	script_object2_ref->test_fn = [&collision_happend](const CollisionEvent & ev) {
		// is static should not be called
		FAIL();
	};
	EXPECT_FALSE(collision_happend);
	Transform & tf = this->mgr.get_components_by_id<Transform>(1).front().get();
	tf.position = {50,25};
	Rigidbody & rg1 = this->mgr.get_components_by_id<Rigidbody>(1).front().get();
	rg1.data.linear_velocity = {10,10};
	Rigidbody & rg2 = this->mgr.get_components_by_id<Rigidbody>(2).front().get();
	rg2.data.body_type = crepe::Rigidbody::BodyType::STATIC;
	collision_sys.update();
	EXPECT_TRUE(collision_happend);
}
