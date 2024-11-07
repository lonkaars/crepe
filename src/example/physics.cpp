#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Transform.h>
#include <crepe/system/PhysicsSystem.h>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	GameObject *game_object;
	game_object = new GameObject(0, "Name", "Tag", Vector2{0,0},0,0);
	game_object->add_component<Rigidbody>(Rigidbody::RigidbodyData{
		.mass = 1,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.constraints = {0,0,0},
		.use_gravity = true,
		.bounce = false,
		});
	return 0;
}
