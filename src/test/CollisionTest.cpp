#include <gtest/gtest.h>

#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Event.h>
#include <crepe/api/EventManager.h>
#include <crepe/api/Script.h>

#include <crepe/ComponentManager.h>
#include <crepe/system/PhysicsSystem.h>


using namespace std;
using namespace std::chrono_literals;
using namespace crepe;


class MyScript : public Script {
	public:
		static crepe::CollisionSystem::CollisionInfo last_collision_info;
	private:
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

class CollisionTest : public ::testing::Test {
public:
	ComponentManager component_manager;
	PhysicsSystem system{component_manager};
	
	void SetUp() override {
		ComponentManager & mgr = this->component_manager;
	}
};

TEST_F(CollisionTest, collision) {
//read static data
const CollisionEvent& test = MyScript::last_collision_info;
}
