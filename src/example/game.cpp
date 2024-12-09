#include "api/CircleCollider.h"
#include "api/Scene.h"
#include "manager/ComponentManager.h"
#include "manager/Mediator.h"
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>

using namespace crepe;

using namespace std;

class MyScript1 : public Script {
	bool flip = false;
	bool oncollision(const CollisionEvent & test) {
		Log::logf("Box {} script on_collision()", test.info.this_collider.game_object_id);
		return true;
	}
	bool keypressed(const KeyPressEvent & test) {
		Log::logf("Box script keypressed()");
		switch (test.key) {
			case Keycode::A: {
				Transform & tf = this->get_component<Transform>();
				tf.position.x -= 1;
				break;
			}
			case Keycode::W: {
				Transform & tf = this->get_component<Transform>();
				tf.position.y -= 1;
				break;
			}
			case Keycode::S: {
				Transform & tf = this->get_component<Transform>();
				tf.position.y += 1;
				break;
			}
			case Keycode::D: {
				Transform & tf = this->get_component<Transform>();
				tf.position.x += 1;
				break;
			}
			case Keycode::E: {
				if (flip) {
					flip = false;
					this->get_component<BoxCollider>().active = true;
					this->get_components<Sprite>()[0].get().active = true;
					this->get_component<CircleCollider>().active = false;
					this->get_components<Sprite>()[1].get().active = false;
				} else {
					flip = true;
					this->get_component<BoxCollider>().active = false;
					this->get_components<Sprite>()[0].get().active = false;
					this->get_component<CircleCollider>().active = true;
					this->get_components<Sprite>()[1].get().active = true;
				}

				//add collider switch
				break;
			}
			default:
				break;
		}
		return false;
	}

	void init() {
		Log::logf("init");
		subscribe<CollisionEvent>(
			[this](const CollisionEvent & ev) -> bool { return this->oncollision(ev); });
		subscribe<KeyPressEvent>(
			[this](const KeyPressEvent & ev) -> bool { return this->keypressed(ev); });
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
	}
};

class MyScript2 : public Script {
	bool flip = false;
	bool oncollision(const CollisionEvent & test) {
		Log::logf("Box {} script on_collision()", test.info.this_collider.game_object_id);
		return true;
	}
	bool keypressed(const KeyPressEvent & test) {
		Log::logf("Box script keypressed()");
		switch (test.key) {
			case Keycode::LEFT: {
				Transform & tf = this->get_component<Transform>();
				tf.position.x -= 1;
				break;
			}
			case Keycode::UP: {
				Transform & tf = this->get_component<Transform>();
				tf.position.y -= 1;
				break;
			}
			case Keycode::DOWN: {
				Transform & tf = this->get_component<Transform>();
				tf.position.y += 1;
				break;
			}
			case Keycode::RIGHT: {
				Transform & tf = this->get_component<Transform>();
				tf.position.x += 1;
				break;
			}
			case Keycode::PAUSE: {
				if (flip) {
					flip = false;
					this->get_component<BoxCollider>().active = true;
					this->get_components<Sprite>()[0].get().active = true;
					this->get_component<CircleCollider>().active = false;
					this->get_components<Sprite>()[1].get().active = false;
				} else {
					flip = true;
					this->get_component<BoxCollider>().active = false;
					this->get_components<Sprite>()[0].get().active = false;
					this->get_component<CircleCollider>().active = true;
					this->get_components<Sprite>()[1].get().active = true;
				}

				//add collider switch
				break;
			}
			default:
				break;
		}
		return false;
	}

	void init() {
		Log::logf("init");
		subscribe<CollisionEvent>(
			[this](const CollisionEvent & ev) -> bool { return this->oncollision(ev); });
		subscribe<KeyPressEvent>(
			[this](const KeyPressEvent & ev) -> bool { return this->keypressed(ev); });
	}
	void update() {
		// Retrieve component from the same GameObject this script is on
	}
};

class ConcreteScene1 : public Scene {
public:
	using Scene::Scene;

	void load_scene() {

		Mediator & m = this->mediator;
		ComponentManager & mgr = m.component_manager;
		Color color(0, 0, 0, 255);

		float screen_size_width = 320;
		float screen_size_height = 240;
		float world_collider = 1000;
		//define playable world
		GameObject world = mgr.new_object(
			"Name", "Tag", vec2{screen_size_width / 2, screen_size_height / 2}, 0, 1);
		world.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 0,
			.gravity_scale = 0,
			.body_type = Rigidbody::BodyType::STATIC,
			.offset = {0, 0},
			.collision_layers = {0},
		});
		world.add_component<BoxCollider>(
			vec2{0, 0 - (screen_size_height / 2 + world_collider / 2)},
			vec2{world_collider, world_collider});
		; // Top
		world.add_component<BoxCollider>(vec2{0, screen_size_height / 2 + world_collider / 2},
										 vec2{world_collider, world_collider}); // Bottom
		world.add_component<BoxCollider>(
			vec2{0 - (screen_size_width / 2 + world_collider / 2), 0},
			vec2{world_collider, world_collider}); // Left
		world.add_component<BoxCollider>(vec2{screen_size_width / 2 + world_collider / 2, 0},
										 vec2{world_collider, world_collider}); // right
		world.add_component<Camera>(
			Color::WHITE,
			ivec2{static_cast<int>(screen_size_width), static_cast<int>(screen_size_height)},
			vec2{screen_size_width, screen_size_height}, 1.0f);

		GameObject game_object1 = mgr.new_object(
			"Name", "Tag", vec2{screen_size_width / 2, screen_size_height / 2}, 0, 1);
		game_object1.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 0,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.linear_velocity = {0, 0},
			.constraints = {0, 0, 0},
			.elastisity_coefficient = 1,
			.offset = {0, 0},
			.collision_layers = {0},
		});
		// add box with boxcollider
		game_object1.add_component<BoxCollider>(vec2{0, 0}, vec2{20, 20});
		game_object1.add_component<BehaviorScript>().set_script<MyScript1>();
		auto img1 = Texture("asset/texture/square.png");
		game_object1.add_component<Sprite>(img1, color, Sprite::FlipSettings{false, false}, 1,
										   1, 20);

		//add circle with cirlcecollider deactiveated
		game_object1.add_component<CircleCollider>(vec2{0, 0}, 10).active = false;
		auto img2 = Texture("asset/texture/circle.png");
		game_object1
			.add_component<Sprite>(img2, color, Sprite::FlipSettings{false, false}, 1, 1, 20)
			.active
			= false;

		GameObject game_object2 = mgr.new_object(
			"Name", "Tag", vec2{screen_size_width / 2, screen_size_height / 2}, 0, 1);
		game_object2.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 0,
			.body_type = Rigidbody::BodyType::STATIC,
			.linear_velocity = {0, 0},
			.constraints = {0, 0, 0},
			.elastisity_coefficient = 1,
			.offset = {0, 0},
			.collision_layers = {0},
		});
		// add box with boxcollider
		game_object2.add_component<BoxCollider>(vec2{0, 0}, vec2{20, 20});
		game_object2.add_component<BehaviorScript>().set_script<MyScript2>();
		auto img3 = Texture("asset/texture/square.png");
		game_object2.add_component<Sprite>(img3, color, Sprite::FlipSettings{false, false}, 1,
										   1, 20);

		//add circle with cirlcecollider deactiveated
		game_object2.add_component<CircleCollider>(vec2{0, 0}, 10).active = false;
		auto img4 = Texture("asset/texture/circle.png");
		game_object2
			.add_component<Sprite>(img4, color, Sprite::FlipSettings{false, false}, 1, 1, 20)
			.active
			= false;
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {

	LoopManager gameloop;
	gameloop.add_scene<ConcreteScene1>();
	gameloop.start();
	return 0;
}
