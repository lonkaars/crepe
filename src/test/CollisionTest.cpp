#include <cstddef>
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
#include <type_traits>


using namespace std;
using namespace std::chrono_literals;
using namespace crepe;


class MyScript : public Script {
	public:
		static const crepe::CollisionSystem::CollisionInfo* last_collision_info;
	private:
		static bool oncollision(const CollisionEvent& test) {
			last_collision_info = &test.info;
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
	
	void SetUp() override {
		MyScript::last_collision_info = nullptr;
		ComponentManager & mgr = this->component_manager;
		if(mgr.get_components_by_id<Transform>(0).empty())
		{
			create_test_world();
			create_test_components();
		}
		reset_test_components();
	}

	void create_test_world() {
		double screen_size_width = 640;
		double screen_size_height = 480;
		double world_collider = 1000;
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

	}

	void reset_test_components()
	{

	}
};

TEST_F(CollisionTest, collision) {
	// change object data before calling update

	// call collision system update
	system.update();
	// should not be nullptr after update
	ASSERT_NE(MyScript::last_collision_info, nullptr);

	// check if values are correct
	EXPECT_EQ(MyScript::last_collision_info->first.collider.game_object_id, 1);
	EXPECT_EQ(MyScript::last_collision_info->second.collider.game_object_id, 2);
}
