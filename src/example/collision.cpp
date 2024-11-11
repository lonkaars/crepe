#include "api/BoxCollider.h"
#include "system/CollisionSystem.h"
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Transform.h>
#include <crepe/system/PhysicsSystem.h>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {

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
	CollisionSystem coltest;
	coltest.update();
	return 0;
}
