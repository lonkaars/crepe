#include "api/BoxCollider.h"
#include "system/CollisionSystem.h"
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Transform.h>
#include <crepe/system/PhysicsSystem.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/util/log.h>

#include <crepe/api/AssetManager.h>
#include <crepe/api/Color.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>

#include <chrono>
#include <memory>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	Color color(0, 0, 0, 0);

	GameObject game_object1(0, "Name", "Tag", Vector2{10, 10}, 0, 1);
	game_object1.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 1,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.constraints = {0, 0, 0},
		.use_gravity = true,
		.bounce = false,
		.offset = {0,0}
	});
	game_object1.add_component<BoxCollider>(Vector2{5, 5}, 5, 5);
	// game_object1.add_component<Sprite>(
	// make_shared<Texture>("/home/jaro/crepe/asset/texture/img.png"), color,
	// FlipSettings{true, true});
	

	GameObject game_object2(1, "Name", "Tag", Vector2{20, 0}, 90, 1);
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
	// game_object2.add_component<Sprite>(
	// make_shared<Texture>("/home/jaro/crepe/asset/texture/img.png"), color,
	// FlipSettings{true, true});

	CollisionSystem coltest;
	coltest.update();
	// auto & sys = crepe::RenderSystem::get_instance();
	// auto start = std::chrono::steady_clock::now();
	// while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
	// 	sys.update();
	// }
	return 0;
}
