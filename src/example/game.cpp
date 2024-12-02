#include <crepe/api/GameObject.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Script.h>
#include <crepe/api/Color.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Vector2.h>
#include <crepe/api/Event.h>
#include <crepe/api/EventManager.h>
#include <crepe/api/LoopManager.h>

using namespace crepe;

using namespace std;

class MyScript : public Script {
	bool oncollision(const CollisionEvent& test) {
		Log::logf("Box {} script on_collision()", test.info.first_collider.game_object_id);
		return true;
	}
	void init() {
		subscribe<CollisionEvent>([this](const CollisionEvent& ev) -> bool {
			return this->oncollision(ev);
		});
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
	}
};


class ConcreteScene1 : public Scene {
public:
	using Scene::Scene;

	void load_scene() {
	ComponentManager & mgr = this->component_manager;
	Color color(0, 0, 0, 0);

	float screen_size_width = 640;
	float screen_size_height = 480;
	float world_collider = 1000;
	//define playable world 
	GameObject world = mgr.new_object("Name", "Tag", vec2{screen_size_width/2, screen_size_height/2}, 0, 1);
	world.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 0,
		.gravity_scale = 0,
		.body_type = Rigidbody::BodyType::STATIC,
		.constraints = {0, 0, 0},
		.offset = {0,0}
	});
	world.add_component<BoxCollider>(vec2{0, 0-(screen_size_height/2+world_collider/2)}, world_collider, world_collider);;	// Top
	world.add_component<BoxCollider>(vec2{0, screen_size_height/2+world_collider/2}, world_collider, world_collider); // Bottom
	world.add_component<BoxCollider>(vec2{0-(screen_size_width/2+world_collider/2), 0}, world_collider, world_collider); // Left
	world.add_component<BoxCollider>(vec2{screen_size_width/2+world_collider/2, 0}, world_collider, world_collider); // right


	GameObject game_object1 = mgr.new_object("Name", "Tag", vec2{screen_size_width/2, screen_size_height/2}, 0, 1);
	game_object1.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 1,
		.gravity_scale = 0.01,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = {1,1},
		.constraints = {0, 0, 0},
		.elastisity = 1,
		.offset = {0,0},
	});
	game_object1.add_component<BoxCollider>(vec2{0, 0}, 20, 20);
	game_object1.add_component<BehaviorScript>().set_script<MyScript>();
	auto img = Texture("asset/texture/green_square.png");
	game_object1.add_component<Sprite>(img, color, Sprite::FlipSettings{false, false}, 1, 1, 500);
	game_object1.add_component<Camera>(Color::WHITE, ivec2{1080, 720},vec2{2000, 2000}, 1.0f);
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {

	LoopManager gameloop;
	gameloop.add_scene<ConcreteScene1>();
	gameloop.start();
	return 0;
}
