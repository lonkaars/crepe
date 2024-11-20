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

class MyScript : public Script {
	static bool oncollision(const CollisionEvent& test) {
		std::cout << "test collision: " << test.info.first.collider.game_object_id << std::endl;
		return true;
	}
	void init() {
		EventManager::get_instance().subscribe<CollisionEvent>(oncollision, this->get_game_object_id());
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
		
	}
};

class PhysicsTest : public ::testing::Test {
public:
	ComponentManager component_manager;
	PhysicsSystem system{component_manager};

	void SetUp() override {
		ComponentManager & mgr = this->component_manager;
		vector<reference_wrapper<Transform>> transforms
			= mgr.get_components_by_id<Transform>(0);
		if (transforms.empty()) {
			auto entity = mgr.new_object("", "", Vector2{0, 0}, 0, 0);
			entity.add_component<Rigidbody>(Rigidbody::Data{
				.mass = 1,
				.gravity_scale = 1,
				.body_type = Rigidbody::BodyType::DYNAMIC,
				.max_linear_velocity = Vector2{10, 10},
				.max_angular_velocity = 10,
				.constraints = {0, 0},
				.use_gravity = true,
				.bounce = false,
			});
		}
		transforms = mgr.get_components_by_id<Transform>(0);
		Transform & transform = transforms.front().get();
		transform.position.x = 0.0;
		transform.position.y = 0.0;
		transform.rotation = 0.0;
		vector<reference_wrapper<Rigidbody>> rigidbodies
			= mgr.get_components_by_id<Rigidbody>(0);
		Rigidbody & rigidbody = rigidbodies.front().get();
		rigidbody.data.angular_velocity = 0;
		rigidbody.data.linear_velocity.x = 0;
		rigidbody.data.linear_velocity.y = 0;
	}
};

TEST_F(PhysicsTest, gravity) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = this->component_manager;
	vector<reference_wrapper<Transform>> transforms = mgr.get_components_by_id<Transform>(0);
	const Transform & transform = transforms.front().get();
	ASSERT_FALSE(transforms.empty());
	EXPECT_EQ(transform.position.y, 0);

	system.update();
	EXPECT_EQ(transform.position.y, 1);

	system.update();
	EXPECT_EQ(transform.position.y, 3);
}
