#include <iostream>
#include <thread>
#include <chrono>
#include "Rigidbody.h"
#include "PhysicsSystem.h"
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/GameObject.h>

using namespace crepe;
using namespace std;


int main(int argc, char* argv[]) {
	PhysicsSystem physicsSystem;
	GameObject * game_object[1];
	game_object[0] = new GameObject(5, "Name", "Tag", 0);
	game_object[0]->add_component<Rigidbody>(10, 11 , BodyType::Dynamic);
	physicsSystem.update(); 
    return 0;
}
