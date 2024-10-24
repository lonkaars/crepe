#include <crepe/ComponentManager.h>
#include <crepe/RenderSystem.h>
#include <crepe/CollisionSystem.h>

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
#include <iostream>
#include <memory>

using namespace crepe::api;
using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	CollisionSystem collision_system;

	GameObject * game_object[2];
	
	Color color(0, 0, 0, 0);

	game_object[0] = new GameObject(0, "Name", "Tag", 0);
	Point point = {
		.x = 20,
		.y = 20,
	};
	game_object[0]->add_component<Transform>(point, 0, 0);
	game_object[0]->add_component<Rigidbody>(1, 1, BodyType::DYNAMIC);
	game_object[0]->add_component<BoxCollider>(6, 6);
	game_object[0]->add_component<CircleCollider>(7);
	game_object[0]->add_component<Sprite>(make_shared<Texture>("/home/jaro/crepe/asset/texture/img.png"),color,FlipSettings{false, false});

	game_object[1] = new GameObject(1, "Name", "Tag", 0);
	point.x = 10;
	point.y = 10;
	game_object[1]->add_component<Transform>(point, 0, 0);
	game_object[1]->add_component<Rigidbody>(1, 1, BodyType::DYNAMIC);
	game_object[1]->add_component<BoxCollider>(5,5);
	game_object[1]->add_component<CircleCollider>(7);

	collision_system.update();
	auto & sys = crepe::RenderSystem::get_instance();
	auto start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		sys.update();
	}
	return 0;
}
