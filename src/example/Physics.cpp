#include <iostream>
#include <thread>
#include <chrono>
#include "Transform.h"
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Force.h>
#include "PhysicsSystem.h"
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>

using namespace crepe::api;
using namespace crepe;
using namespace std;


int main(int argc, char* argv[]) {
	PhysicsSystem physicsSystem;
	GameObject * game_object[2];
	game_object[1] = new GameObject(2, "Name", "Tag", 0); // not found not used
	game_object[0] = new GameObject(5, "Name", "Tag", 0);
	Position position = {0, 0};
	game_object[0]->add_component<Transform>(position,0,0);
	game_object[0]->add_component<Rigidbody>(1, 1 , BodyType::Dynamic);
	game_object[0]->add_component<Force>(1 , 0);
	physicsSystem.update(); 
    return 0;
}
