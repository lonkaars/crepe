#include "PhysicsSystem.h"
#include <chrono>
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/Force.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <iostream>
#include <thread>

using namespace crepe::api;
using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	PhysicsSystem physics_system;
	GameObject * game_object[2];
	// not found not used
	game_object[1] = new GameObject(2, "Name", "Tag", Point{0, 0}, 0, 0);
	game_object[0] = new GameObject(5, "Name", "Tag", Point{0, 0}, 0, 0);
	game_object[0]->add_component<Rigidbody>(1, 1, BodyType::DYNAMIC);
	game_object[0]->add_component<Force>(1, 0);
	physics_system.update();
	return 0;
}
