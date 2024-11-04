#include <crepe/ComponentManager.h>
#include <crepe/RenderSystem.h>
#include <crepe/CollisionSystem.h>
#include <crepe/api/AssetManager.h>
#include <crepe/PhysicsSystem.h>
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


#include <chrono>
#include <thread>
#include <iostream>
#include <memory>

using namespace crepe::api;
using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	LoopManager gameLoop;
	GameObject * game_object[2];
	Color color(0, 0, 0, 0);
	game_object[0] = new GameObject(0, "Name", "Tag", 0);
	game_object[0]->add_component<Camera>(Color::get_white());
	game_object[0]->add_component<Transform>(Vector2{20,20}, 0, 1);
	game_object[0]->add_component<Rigidbody>(0.1, 1, Rigidbody::BodyType::DYNAMIC,Vector2{0,0},Vector2{100,100},Vector2{0,0},1,100,0,Rigidbody::physics_constraints{0,0,0},1,0);
	game_object[0]->add_component<BoxCollider>(20, 20);
	game_object[0]->add_component<CircleCollider>(7);
	game_object[0]->add_component<Sprite>(make_shared<Texture>("/home/jaro/crepe/asset/texture/green_square.png"),color,FlipSettings{true, true});

	game_object[1] = new GameObject(1, "Name", "Tag", 0);
	game_object[1]->add_component<Transform>(Vector2{20,80}, 0, 1);
	game_object[1]->add_component<Rigidbody>(1, 1, Rigidbody::BodyType::STATIC,Vector2{0,0},Vector2{100,100},Vector2{0,0},0,100,0,Rigidbody::physics_constraints{0,0,0},1,0);
	game_object[1]->add_component<BoxCollider>(20,20);
	game_object[1]->add_component<CircleCollider>(7);
	game_object[1]->add_component<Sprite>(make_shared<Texture>("/home/jaro/crepe/asset/texture/red_square.png"),color,FlipSettings{true, true});

	gameLoop.setRunning(true);
	gameLoop.setup();
	gameLoop.loop();
	return 0;
}
