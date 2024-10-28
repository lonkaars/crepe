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
	// LoopManager gameLoop;
	CollisionSystem collision_system;
	// collision_system.update();
	// EventManager::getInstance().dispatchEvents();
	// gameLoop.setRunning(true);
	// gameLoop.setup();
	// gameLoop.loop();
	PhysicsSystem physics_system;
	// auto & mgr = AssetManager::get_instance();
	GameObject * game_object[2];
	
	Color color(0, 0, 0, 0);

	game_object[0] = new GameObject(0, "Name", "Tag", 0);
	Point point = {
		.x = 20,
		.y = 20,
	}; 
	game_object[0]->add_component<Transform>(point, 0, 1);
	game_object[0]->add_component<Rigidbody>(1, 1, BodyType::DYNAMIC);
	game_object[0]->add_component<BoxCollider>(20, 20);
	game_object[0]->add_component<CircleCollider>(7);
	game_object[0]->add_component<Sprite>(make_shared<Texture>("/home/jaro/crepe/asset/texture/green_square.png"),color,FlipSettings{true, true});

	game_object[1] = new GameObject(1, "Name", "Tag", 0);
	point.x = 20;
	point.y = 50;
	game_object[1]->add_component<Transform>(point, 0, 1);
	game_object[1]->add_component<Rigidbody>(1, 1, BodyType::STATIC);
	game_object[1]->add_component<BoxCollider>(20,20);
	game_object[1]->add_component<CircleCollider>(7);
	game_object[1]->add_component<Sprite>(make_shared<Texture>("/home/jaro/crepe/asset/texture/red_square.png"),color,FlipSettings{true, true});

	
	auto & sys = crepe::RenderSystem::get_instance();
	auto start = std::chrono::steady_clock::now();
	while (true) {
		auto loop_start = std::chrono::steady_clock::now();

		sys.update();
		physics_system.update();
		collision_system.update();

		// Calculate the duration of the current loop and sleep if needed
		auto loop_end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(loop_end - loop_start).count();
		int target_ms = 60;
		if (elapsed_ms < target_ms) {
			std::this_thread::sleep_for(std::chrono::milliseconds(target_ms - elapsed_ms));
		}
	}
	return 0;
}
