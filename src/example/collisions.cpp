#include <crepe/ComponentManager.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/system/CollisionSystem.h>
#include <crepe/api/AssetManager.h>
#include <crepe/system/PhysicsSystem.h>
#include <crepe/api/loopManager.h>

#include <crepe/Component.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Color.h>

#include <memory>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	LoopManager game_loop;
	GameObject * game_object[2];
	Color color(0, 0, 0, 0);
	game_object[0] = new GameObject(0, "Name", "Tag", Vector2{0,0},0,0);
	game_object[0]->add_component<Camera>(Color::get_white());
	game_object[0]->add_component<Rigidbody>(Rigidbody::RigidbodyData{
		.mass = 1,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.constraints = {0,0,0},
		.use_gravity = true,
		.bounce = false,
		});
	game_object[0]->add_component<BoxCollider>(20, 20);
	game_object[0]->add_component<CircleCollider>(7);
	game_object[0]->add_component<Sprite>(make_shared<Texture>("/home/jaro/crepe/asset/texture/green_square.png"),color,FlipSettings{true, true});

	game_object[1] = new GameObject(1, "Name", "Tag", Vector2{0,0},0,0);
	
	game_object[1]->add_component<Rigidbody>(Rigidbody::RigidbodyData{
		.mass = 1,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::STATIC,
		.constraints = {0,0,0},
		.use_gravity = true,
		.bounce = false,
		});
	game_object[1]->add_component<BoxCollider>(20,20);
	game_object[1]->add_component<CircleCollider>(7);
	game_object[1]->add_component<Sprite>(make_shared<Texture>("/home/jaro/crepe/asset/texture/red_square.png"),color,FlipSettings{true, true});

	game_loop.setRunning(true);
	game_loop.setup();
	game_loop.loop();
	return 0;
}
