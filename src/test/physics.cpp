#include <gtest/gtest.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/system/PhysicsSystem.h>
#include <crepe/api/Config.h>


using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class PhysicsTest : public ::testing::Test {
protected:
    GameObject* game_object;
    PhysicsSystem physics_system;

    void SetUp() override {
        game_object = new GameObject(0,"","",Vector2{0,0},0,0);
        game_object->add_component<Rigidbody>(Rigidbody::RigidbodyData{
            .mass = 1,
            .gravity_scale = 1,
            .body_type = Rigidbody::BodyType::DYNAMIC,
            .constraints = {0, 0},
            .use_gravity = true,
            .bounce = false
        });
    }

    void TearDown() override {
        delete game_object;
    }
};

// Test for linear movement
TEST_F(PhysicsTest, gravity) {
	Config::get_instance().physics.gravity = 1;
	ComponentManager & mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<Transform>> transforms = mgr.get_components_by_id<Transform>(0);
	const Transform& transform = transforms.front().get();
	ASSERT_FALSE(transforms.empty());
	EXPECT_EQ(transform.position.y, 0);
	physics_system.update();
	EXPECT_EQ(transform.position.y, 1); // Update expected result
}


