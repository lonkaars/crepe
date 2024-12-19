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
	bool movement = false;
	bool oncollision(const CollisionEvent & test) {
		Log::logf("Box {} script on_collision()", test.info.self.metadata.game_object_id);
		return true;
	}
	bool keypressed(const KeyPressEvent & test) {
		Log::logf("Box script keypressed()");
		switch (test.key) {
			case Keycode::A: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				Transform & tr = this->get_component<Transform>();
				if(movement) tf.data.linear_velocity.x -= 1;
				else tr.position.x -= 1;
				break;
			}
			case Keycode::W: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				Transform & tr = this->get_component<Transform>();
				if(movement) tf.data.linear_velocity.y -= 1;
				else tr.position.y -= 1;
				break;
			}
			case Keycode::S: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				Transform & tr = this->get_component<Transform>();
				if(movement) tf.data.linear_velocity.y += 1;
				else tr.position.y += 1;
				break;
			}
			case Keycode::D: {
				Rigidbody & tf = this->get_component<Rigidbody>();
				Transform & tr = this->get_component<Transform>();
				if(movement) tf.data.linear_velocity.x += 1;
				else tr.position.x += 1;
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

				break;
			}
			case Keycode::Q: {
				if(movement){
					movement = false; 
					Rigidbody & tf = this->get_component<Rigidbody>();
					tf.data.linear_velocity = {0,0};
				}
				else{
					movement = true;
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
			.gravity_scale = 0,
			.body_type = Rigidbody::BodyType::KINEMATIC,
			.elastisity_coefficient = 1,
		});
		// add box with boxcollider
		game_object1.add_component<BoxCollider>(vec2{20, 20});
		game_object1.add_component<BehaviorScript>().set_script<MyScript1>();

		Asset img1{"asset/texture/test_ap43.png"};
		game_object1.add_component<Sprite>(img1, Sprite::Data{
													 .size = {20, 20},
													 .position_offset = {0, 0},
												 });

		//add circle with cirlcecollider deactiveated
		game_object1.add_component<CircleCollider>(10).active = false;
		Asset img2{"asset/texture/circle.png"};
		game_object1.add_component<Sprite>(img2, Sprite::Data{ 
													 .size = {20, 20},
													 .position_offset = {0, 0}, }).active = false;
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {

	LoopManager gameloop;
	gameloop.add_scene<ConcreteScene1>();
	gameloop.start();
	return 0;
};
