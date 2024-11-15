#include "api/BoxCollider.h"
#include "system/CollisionSystem.h"
#include <crepe/system/ScriptSystem.h>
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Transform.h>
#include <crepe/system/PhysicsSystem.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/util/log.h>

#include <crepe/api/Script.h>
#include <crepe/api/AssetManager.h>
#include <crepe/api/Color.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <crepe/api/Event.h>
#include <crepe/api/EventManager.h>

#include <chrono>
#include <memory>

using namespace crepe;
using namespace std;

class MyScript : public Script {
	static bool oncollision(const CollisionEvent& test) {
		std::cout << "test collision: " << test.info.first.collider.game_object_id << std::endl;
		return true;
	}
	void init() {
		EventManager::get_instance().subscribe<CollisionEvent>(oncollision, this->parent->game_object_id);
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
		
	}
	
	
};

int main(int argc, char * argv[]) {
	Color color(0, 0, 0, 0);

	GameObject game_object1(0, "Name", "Tag", Vector2{10, 10}, 0, 1);
	game_object1.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 1,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.constraints = {0, 0, 0},
		.use_gravity = true,
		.bounce = true,
		.offset = {0,0}
	});
	game_object1.add_component<BoxCollider>(Vector2{5, 5}, 5, 5);
	game_object1.add_component<BehaviorScript>().set_script<MyScript>();
	game_object1.add_component<BehaviorScript>().set_script<MyScript>();

	// game_object1.add_component<Sprite>(
	// make_shared<Texture>("/home/jaro/crepe/asset/texture/img.png"), color,
	// FlipSettings{true, true});
	

	GameObject game_object2(1, "Name", "Tag", Vector2{10, 10}, 0, 1);
	game_object2.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 1,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.constraints = {0, 0, 0},
		.use_gravity = true,
		.bounce = false,
		.offset = {0,0}
	});
	game_object2.add_component<BoxCollider>(Vector2{5, 5}, 5, 5);
	game_object2.add_component<BehaviorScript>().set_script<MyScript>();
	// game_object2.add_component<Sprite>(
	// make_shared<Texture>("/home/jaro/crepe/asset/texture/img.png"), color,
	// FlipSettings{true, true});

	
	ScriptSystem sys;
	// Update all scripts. This should result in MyScript::update being called
	sys.update();
	// auto & sys = crepe::RenderSystem::get_instance();
	// auto start = std::chrono::steady_clock::now();
	// while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
	// 	sys.update();
	// }
	CollisionSystem coltest;
	coltest.update();



	return 0;
}
