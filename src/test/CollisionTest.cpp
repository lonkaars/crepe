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

class CollisionHandler : public Script {
public:
	int box_id;
	EventManager & evmgr = EventManager::get_instance();

	CollisionHandler(int box_id) {
		this->box_id = box_id;
	}

	bool on_collision(const CollisionEvent& ev) {
		Log::logf("Box {} event x={} y={}", box_id, ev.info.move_back_value.x, ev.info.move_back_value.y);
		return true;
	}

	void init() {
		Log::logf("Box {} script init()", box_id);

		subscribe<CollisionEvent>([this](const CollisionEvent & ev) {
			return this->on_collision(ev);
		});
	}
};

class CollisionTest : public Test {
public:
	ComponentManager mgr;
	CollisionSystem collision_sys{mgr};
	ScriptSystem script_sys{mgr};

	GameObject world = mgr.new_object("world");
	GameObject game_object1 = mgr.new_object("object1", "", { 0, 0 });
	GameObject game_object2 = mgr.new_object("object2", "", { 0, 0 });

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
		world.add_component<BoxCollider>(Vector2{5, 11}, 10, 2); // Top
		world.add_component<BoxCollider>(Vector2{5, -1}, 10, 2); // Bottom
		world.add_component<BoxCollider>(Vector2{-1, 5}, 2, 10); // Left
		world.add_component<BoxCollider>(Vector2{11, 5}, 2, 10); // right

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
		BehaviorScript & script_object1 = game_object1.add_component<BehaviorScript>().set_script<CollisionHandler>(1);
		script_object1_ref = static_cast<CollisionHandler*>(script_object1.script.get());
		ASSERT_NE(script_object1_ref, nullptr);
		
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
		BehaviorScript & script_object2 = game_object2.add_component<BehaviorScript>().set_script<CollisionHandler>(2);
		script_object2_ref = static_cast<CollisionHandler*>(script_object2.script.get());
		ASSERT_NE(script_object2_ref, nullptr);

		// Ensure Script::init() is called on all BehaviorScript instances
		script_sys.update();
	}
};

TEST_F(CollisionTest, collision_example) {
	collision_sys.update();
}

TEST_F(CollisionTest, collision_box_box_dynamic) {
	collision_sys.update();
}
