#include <crepe/util/Log.h>
#include <crepe/api/Engine.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Camera.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Config.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Event.h>

using namespace crepe;
using namespace std;

class PlayerController : public Script {
	void update() {
		Rigidbody & body = get_component<Rigidbody>();

		if (get_key_state(Keycode::SPACE))
			body.add_force_linear({ 0, -1 });

		body.data.linear_velocity.x =
			-5 * get_key_state(Keycode::A)
			+ 5 * get_key_state(Keycode::D);
	}
};

class DemoScene : public Scene {
	string get_name() const override { return "DemoScene"; }
	void load_scene() override {
		GameObject camera = new_object("camera");
		camera.add_component<Camera>(vec2{10, 10}, Camera::Data{
			.bg_color = {0x22, 0x22, 0x22},
		});


		GameObject ground = new_object("ground");
		Sprite & ground_sprite = ground.add_component<Sprite>(
			Asset{"asset/demo/floor.png"},
			Sprite::Data{
				.size = {10, 2},
			}
		);
		ground.transform.position = {0, 4};
		ground.add_component<Rigidbody>(Rigidbody::Data{
			.body_type = Rigidbody::BodyType::STATIC,
		});
		ground.add_component<BoxCollider>(ground_sprite.data.size);


		GameObject player = new_object("player");
		Sprite & player_sprite = player.add_component<Sprite>(
			Asset{"asset/demo/player.png"},
			Sprite::Data{
				.size = { 1, 1 },
			}
		);
		player.add_component<Rigidbody>(Rigidbody::Data{
			.elastisity_coefficient = 0.66,
		});
		player.add_component<BoxCollider>(player_sprite.data.size);
		player.add_component<BehaviorScript>().set_script<PlayerController>();
	}
};

int main() {
	Config::get_instance() = {
		.physics = {
			.gravity = 20,
		},
		.window = {
			.size = {800, 800},
		},
	};

	Engine demo;
	demo.add_scene<DemoScene>();
	return demo.main();
}

