#include "api/CircleCollider.h"
#include "api/ParticleEmitter.h"
#include "api/Scene.h"
#include "manager/ComponentManager.h"
#include "manager/Mediator.h"
#include "types.h"
#include <cmath>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>

using namespace crepe;

using namespace std;

class MyScript1 : public Script {
	bool flip = false;
	bool oncollision(const CollisionEvent & test) {
		Log::logf("Box {} script on_collision()", test.info.self.metadata.game_object_id);
		return true;
	}
	bool keypressed(const KeyPressEvent & test) {
		Log::logf("Box script keypressed()");
		switch (test.key) {
			case Keycode::A: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				tf.data.linear_velocity.x -= 1;
				break;
			}
			case Keycode::W: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				// tf.data.linear_velocity.y -= 1;
				tf.add_force_linear({0, -1});
				break;
			}
			case Keycode::S: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				tf.data.linear_velocity.y += 1;
				break;
			}
			case Keycode::D: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				tf.data.linear_velocity.x += 1;
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
		Rigidbody & tf = this->get_component<Rigidbody>();
		Log::logf("linear_velocity.x {}", tf.data.linear_velocity.x);
		Log::logf("linear_velocity.y {}", tf.data.linear_velocity.y);
		// tf.data.linear_velocity = {0,0};
	}
};

class MyScript2 : public Script {
	bool flip = false;
	bool oncollision(const CollisionEvent & test) {
		Log::logf("Box {} script on_collision()", test.info.self.metadata.game_object_id);
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
			case Keycode::J: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				tf.data.linear_velocity.x = -10;
				break;
			}
			case Keycode::I: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				tf.data.linear_velocity.y -= 1;
				break;
			}
			case Keycode::K: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				tf.data.linear_velocity.y += 1;
				break;
			}
			case Keycode::L: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				tf.data.linear_velocity.x = 10;
				break;
			}
			case Keycode::O: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				tf.data.linear_velocity.x = 0;
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

		Color color(0, 0, 0, 255);

		float screen_size_width = 320;
		float screen_size_height = 240;
		float world_collider = 1000;
		//define playable world
		GameObject world = new_object(
			"Name", "Tag", vec2{screen_size_width / 2, screen_size_height / 2}, 0, 1);
		world.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 0,
			.body_type = Rigidbody::BodyType::STATIC,
		});
		world.add_component<BoxCollider>(
			vec2{world_collider, world_collider},
			vec2{0, 0 - (screen_size_height / 2 + world_collider / 2)}); // Top
		world.add_component<BoxCollider>(
			vec2{world_collider, world_collider},
			vec2{0, screen_size_height / 2 + world_collider / 2}); // Bottom
		world.add_component<BoxCollider>(
			vec2{world_collider, world_collider},git stauts
			vec2{0 - (screen_size_width / 2 + world_collider / 2), 0}); // Left
		world.add_component<BoxCollider>(
			vec2{world_collider, world_collider},
			vec2{screen_size_width / 2 + world_collider / 2, 0}); // right
		world.add_component<Camera>(
			ivec2{static_cast<int>(screen_size_width), static_cast<int>(screen_size_height)},
			vec2{screen_size_width, screen_size_height},
			Camera::Data{
				.bg_color = Color::WHITE,
				.zoom = 1,
			});

		GameObject game_object1 = new_object(
			"Name", "Tag", vec2{screen_size_width / 2, screen_size_height / 2+60}, 0, 1);
		game_object1.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 0,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.linear_velocity = {0, 0},
			.constraints = {0, 0, 0},
			.elastisity_coefficient = 1,
		});
		// add box with boxcollider
		game_object1.add_component<BoxCollider>(vec2{20, 20});
		game_object1.add_component<BehaviorScript>().set_script<MyScript1>();

		Asset img1{"asset/texture/test_ap43.png"};
		game_object1.add_component<Sprite>(img1, Sprite::Data{
													 .sorting_in_layer = 2,
													 .order_in_layer = 2,
													 .size = {20, 20},
													 .position_offset = {0, 0},
												 });

		//add circle with cirlcecollider deactiveated
		game_object1.add_component<CircleCollider>(10).active = false;
		Asset img2{"asset/texture/circle.png"};
		game_object1
			.add_component<Sprite>(img2,
								   Sprite::Data{
									   .size = {20, 20},
								   })
			.active
			= false;

		GameObject game_object2 = new_object(
			"Name", "Tag", vec2{screen_size_width / 2, screen_size_height / 2}, 0, 1);
		game_object2.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1,
			.gravity_scale = 1,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.linear_velocity = {0, 0},
			.constraints = {0, 0, 0},
			.elastisity_coefficient = 1,
		});
		// add box with boxcollider
		game_object2.add_component<BoxCollider>(vec2{20, 20});
		game_object2.add_component<BehaviorScript>().set_script<MyScript2>();

		game_object2.add_component<Sprite>(img1, Sprite::Data{
													 .size = {20, 20},
												 });

		//add circle with cirlcecollider deactiveated
		game_object2.add_component<CircleCollider>(10).active = false;

		game_object2
			.add_component<Sprite>(img2,
								   Sprite::Data{
									   .size = {20, 20},
								   })
			.active
			= false;
		Asset img5{"asset/texture/square.png"};

		GameObject particle = new_object(
			"Name", "Tag", vec2{screen_size_width / 2, screen_size_height / 2}, 0, 1);
		auto & particle_image = particle.add_component<Sprite>(img5, Sprite::Data{
																		 .size = {5, 5},
																	 });
		auto & test
			= particle.add_component<ParticleEmitter>(particle_image, ParticleEmitter::Data{
																		  .offset = {0, 0},
																		  .max_particles = 256,
																		  .emission_rate = 1,
																		  .min_speed = 10,
																		  .max_speed = 20,
																		  .min_angle = -20,
																		  .max_angle = 20,
																		  .begin_lifespan = 0,
																		  .end_lifespan = 5,
																	  });
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {

	LoopManager gameloop;
	gameloop.add_scene<ConcreteScene1>();
	gameloop.start();
	return 0;
}
