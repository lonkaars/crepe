#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/LoopTimerManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/system/PhysicsSystem.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class PhysicsTest : public ::testing::Test {
	Mediator m;

public:
	ComponentManager component_manager{m};
	PhysicsSystem system{m};
	LoopTimerManager loop_timer{m};

	void SetUp() override {
		ComponentManager & mgr = this->component_manager;
		vector<reference_wrapper<Transform>> transforms
			= mgr.get_components_by_id<Transform>(0);
		if (transforms.empty()) {
			auto entity = mgr.new_object("", "", vec2{0, 0}, 0, 0);
			entity.add_component<Rigidbody>(Rigidbody::Data{
				.mass = 1,
				.gravity_scale = 1,
				.body_type = Rigidbody::BodyType::DYNAMIC,
				.max_linear_velocity = 10,
				.max_angular_velocity = 10,
				.constraints = {0, 0},
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

	system.fixed_update();
	EXPECT_NEAR(transform.position.y, 0.0004, 0.0001);

	system.fixed_update();
	EXPECT_NEAR(transform.position.y, 0.002, 0.001);
}

TEST_F(PhysicsTest, max_velocity) {
	ComponentManager & mgr = this->component_manager;
	vector<reference_wrapper<Rigidbody>> rigidbodies = mgr.get_components_by_id<Rigidbody>(0);
	Rigidbody & rigidbody = rigidbodies.front().get();
	rigidbody.data.gravity_scale = 0;
	ASSERT_FALSE(rigidbodies.empty());
	EXPECT_EQ(rigidbody.data.linear_velocity.y, 0);

	rigidbody.add_force_linear({100, 100});
	rigidbody.add_force_angular(100);
	system.fixed_update();
	EXPECT_NEAR(rigidbody.data.linear_velocity.y, 7.07, 0.01);
	EXPECT_NEAR(rigidbody.data.linear_velocity.x, 7.07, 0.01);
	EXPECT_EQ(rigidbody.data.angular_velocity, 10);

	rigidbody.add_force_linear({-100, -100});
	rigidbody.add_force_angular(-100);
	system.fixed_update();
	EXPECT_NEAR(rigidbody.data.linear_velocity.y, -7.07, 0.01);
	EXPECT_NEAR(rigidbody.data.linear_velocity.x, -7.07, 0.01);
	EXPECT_EQ(rigidbody.data.angular_velocity, -10);
}

TEST_F(PhysicsTest, movement) {
	ComponentManager & mgr = this->component_manager;
	vector<reference_wrapper<Rigidbody>> rigidbodies = mgr.get_components_by_id<Rigidbody>(0);
	Rigidbody & rigidbody = rigidbodies.front().get();
	rigidbody.data.gravity_scale = 0;
	vector<reference_wrapper<Transform>> transforms = mgr.get_components_by_id<Transform>(0);
	const Transform & transform = transforms.front().get();
	ASSERT_FALSE(rigidbodies.empty());
	ASSERT_FALSE(transforms.empty());

	rigidbody.add_force_linear({1, 1});
	rigidbody.add_force_angular(1);
	system.fixed_update();
	EXPECT_NEAR(transform.position.x, 0.02, 0.001);
	EXPECT_NEAR(transform.position.y, 0.02, 0.001);
	EXPECT_NEAR(transform.rotation, 0.02, 0.001);

	rigidbody.data.constraints = {1, 1, 1};
	EXPECT_NEAR(transform.position.x, 0.02, 0.001);
	EXPECT_NEAR(transform.position.y, 0.02, 0.001);
	EXPECT_NEAR(transform.rotation, 0.02, 0.001);
	rigidbody.data.constraints = {0, 0, 0};
	rigidbody.data.linear_velocity_coefficient.x = 0.5;
	rigidbody.data.linear_velocity_coefficient.y = 0.5;
	rigidbody.data.angular_velocity_coefficient = 0.5;
	system.fixed_update();
	EXPECT_NEAR(rigidbody.data.linear_velocity.x, 0.98, 0.01);
	EXPECT_NEAR(rigidbody.data.linear_velocity.y, 0.98, 0.01);
	EXPECT_NEAR(rigidbody.data.angular_velocity, 0.98, 0.01);

	rigidbody.data.constraints = {1, 1, 0};
	rigidbody.data.angular_velocity_coefficient = 0;
	rigidbody.data.max_angular_velocity = 1000;
	rigidbody.data.angular_velocity = 360;
	system.fixed_update();
	EXPECT_NEAR(transform.rotation, 7.24, 0.01);

	rigidbody.data.angular_velocity = -360;
	system.fixed_update();
	EXPECT_NEAR(transform.rotation, 0.04, 0.001);
	system.fixed_update();
	EXPECT_NEAR(transform.rotation, 352.84, 0.01);
}
