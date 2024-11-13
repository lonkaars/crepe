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

class PhysicsTest : public ::testing::Test {
public:
	ComponentManager component_manager;
	PhysicsSystem system { component_manager };

	void SetUp() override {
		ComponentManager & mgr = this->component_manager;
		vector<reference_wrapper<Transform>> transforms
			= mgr.get_components_by_id<Transform>(0);
		if (transforms.empty()) {
			auto & entity = mgr.new_object("", "", Vector2{0, 0}, 0, 0);
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

TEST_F(PhysicsTest, max_velocity) {
	ComponentManager & mgr = this->component_manager;
	vector<reference_wrapper<Rigidbody>> rigidbodies
		= mgr.get_components_by_id<Rigidbody>(0);
	Rigidbody & rigidbody = rigidbodies.front().get();
	ASSERT_FALSE(rigidbodies.empty());
	EXPECT_EQ(rigidbody.data.linear_velocity.y, 0);

	rigidbody.add_force_linear({100, 100});
	rigidbody.add_force_angular(100);
	system.update();
	EXPECT_EQ(rigidbody.data.linear_velocity.y, 10);
	EXPECT_EQ(rigidbody.data.linear_velocity.x, 10);
	EXPECT_EQ(rigidbody.data.angular_velocity, 10);

	rigidbody.add_force_linear({-100, -100});
	rigidbody.add_force_angular(-100);
	system.update();
	EXPECT_EQ(rigidbody.data.linear_velocity.y, -10);
	EXPECT_EQ(rigidbody.data.linear_velocity.x, -10);
	EXPECT_EQ(rigidbody.data.angular_velocity, -10);
}

TEST_F(PhysicsTest, movement) {
	Config::get_instance().physics.gravity = 0;
	ComponentManager & mgr = this->component_manager;
	vector<reference_wrapper<Rigidbody>> rigidbodies = mgr.get_components_by_id<Rigidbody>(0);
	Rigidbody & rigidbody = rigidbodies.front().get();
	vector<reference_wrapper<Transform>> transforms = mgr.get_components_by_id<Transform>(0);
	const Transform & transform = transforms.front().get();
	ASSERT_FALSE(rigidbodies.empty());
	ASSERT_FALSE(transforms.empty());

	rigidbody.add_force_linear({1, 1});
	rigidbody.add_force_angular(1);
	system.update();
	EXPECT_EQ(transform.position.x, 1);
	EXPECT_EQ(transform.position.y, 1);
	EXPECT_EQ(transform.rotation, 1);

	rigidbody.data.constraints = {1, 1, 1};
	EXPECT_EQ(transform.position.x, 1);
	EXPECT_EQ(transform.position.y, 1);
	EXPECT_EQ(transform.rotation, 1);

	rigidbody.data.linear_damping.x = 0.5;
	rigidbody.data.linear_damping.y = 0.5;
	rigidbody.data.angular_damping = 0.5;
	system.update();
	EXPECT_EQ(rigidbody.data.linear_velocity.x, 0.5);
	EXPECT_EQ(rigidbody.data.linear_velocity.y, 0.5);
	EXPECT_EQ(rigidbody.data.angular_velocity, 0.5);

	rigidbody.data.constraints = {1, 1, 0};
	rigidbody.data.angular_damping = 0;
	rigidbody.data.max_angular_velocity = 1000;
	rigidbody.data.angular_velocity = 360;
	system.update();
	EXPECT_EQ(transform.rotation, 1);

	rigidbody.data.angular_velocity = -360;
	system.update();
	EXPECT_EQ(transform.rotation, 1);
}
