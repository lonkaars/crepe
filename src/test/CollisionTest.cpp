#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Vector2.h"
#include <crepe/ComponentManager.h>
#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/system/PhysicsSystem.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class CollisionTest : public ::testing::Test {
protected:
	GameObject * game_object1;
	GameObject * game_object2;
	PhysicsSystem physics_system;
	void SetUp() override {
		ComponentManager & mgr = ComponentManager::get_instance();
		std::vector<std::reference_wrapper<Transform>> transforms
			= mgr.get_components_by_id<Transform>(0);
		if (transforms.empty()) {
			double width,height,radius = 10;
			// ob 1
			game_object1 = new GameObject(0, "", "", Vector2{0, 0}, 0, 0);
			game_object1->add_component<Rigidbody>(Rigidbody::Data{
				.mass = 1,
				.gravity_scale = 1,
				.body_type = Rigidbody::BodyType::DYNAMIC,
				.max_linear_velocity = Vector2{10, 10},
				.max_angular_velocity = 10,
				.constraints = {0, 0},
				.use_gravity = true,
				.bounce = false,
			});
			
			game_object1->add_component<BoxCollider>(Vector2{0,0},width,height);
			game_object1->add_component<CircleCollider>(Vector2{0,0},radius);

			//ob 2
			game_object2 = new GameObject(0, "", "", Vector2{0, 0}, 0, 0);
			game_object2->add_component<Rigidbody>(Rigidbody::Data{
				.mass = 1,
				.gravity_scale = 1,
				.body_type = Rigidbody::BodyType::DYNAMIC,
				.max_linear_velocity = Vector2{10, 10},
				.max_angular_velocity = 10,
				.constraints = {0, 0},
				.use_gravity = true,
				.bounce = false,
			});
			game_object2->add_component<BoxCollider>(Vector2{0,0},width,height);
			game_object2->add_component<CircleCollider>(Vector2{0,0},radius);

		}
		for (int i = 0; i < 2; i ++) {
			transforms = mgr.get_components_by_id<Transform>(i);
			Transform & transform = transforms.front().get();
			transform.position.x = 0.0;
			transform.position.y = 0.0;
			transform.rotation = 0.0;
			std::vector<std::reference_wrapper<Rigidbody>> rigidbodies
				= mgr.get_components_by_id<Rigidbody>(i);
			Rigidbody & rigidbody = rigidbodies.front().get();
			rigidbody.data.angular_velocity = 0;
			rigidbody.data.linear_velocity.x = 0;
			rigidbody.data.linear_velocity.y = 0;
			std::vector<std::reference_wrapper<BoxCollider>> boxcolliders
				= mgr.get_components_by_id<BoxCollider>(i);
			BoxCollider & box_collider = boxcolliders.front().get();
			box_collider.offset = {0,0};
			box_collider.width = 10;
			box_collider.height = 10;
			std::vector<std::reference_wrapper<CircleCollider>> circlecolliders
				= mgr.get_components_by_id<CircleCollider>(i);
			CircleCollider & circle_collider = circlecolliders.front().get();
			circle_collider.offset = {0,0};
			circle_collider.radius = 10;
		}
		
	}
};

TEST_F(CollisionTest, box_box_collision) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<Transform>> transforms
		= mgr.get_components_by_id<Transform>(0);
	const Transform & transform = transforms.front().get();
	ASSERT_FALSE(transforms.empty());
	EXPECT_EQ(transform.position.y, 0);
	physics_system.update();
	EXPECT_EQ(transform.position.y, 1);
	physics_system.update();
	EXPECT_EQ(transform.position.y, 3);
}

