#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Vector2.h"
#include <crepe/ComponentManager.h>
#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/system/CollisionSystem.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class CollisionTest : public ::testing::Test {
protected:
	GameObject * game_object1;
	GameObject * game_object2;
	CollisionSystem collision_system;
	void SetUp() override {
		ComponentManager & mgr = ComponentManager::get_instance();
		mgr.delete_all_components();
		std::vector<std::reference_wrapper<Transform>> transforms
			= mgr.get_components_by_id<Transform>(0);

		// ob 1
		game_object1 = new GameObject(0, "", "", Vector2{0, 0}, 0, 0);
		game_object1->add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 1,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.max_linear_velocity = Vector2{10, 10},
			.max_angular_velocity = 10,
			.constraints = {0, 0, 0},
			.use_gravity = false,
			.bounce = false,
		});
		
		game_object1->add_component<BoxCollider>(Vector2{0,0},10,10);
		

		//ob 2
		game_object2 = new GameObject(1, "", "", Vector2{50, 50}, 0, 0);
		game_object2->add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 1,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.max_linear_velocity = Vector2{10, 10},
			.max_angular_velocity = 10,
			.constraints = {0, 0, 0},
			.use_gravity = false,
			.bounce = false,
		});
		game_object2->add_component<BoxCollider>(Vector2{0,0},10,10);
	}
};

TEST_F(CollisionTest, box_box_collision) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<Transform>> transforms
		= mgr.get_components_by_id<Transform>(0);
	Transform & transform = transforms.front().get();
	ASSERT_FALSE(transforms.empty());
	transform.position = {39,50};
	collision_system.update();
	transform.position = {40,50};
	collision_system.update();
	transform.position = {41,50};
	collision_system.update();
	transform.position = {44,50};
	collision_system.update();
	transform.position = {50,50};
	collision_system.update();
}

