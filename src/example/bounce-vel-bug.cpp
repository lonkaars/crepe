#include <crepe/api/LoopManager.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/BoxCollider.h>

using namespace crepe;
using namespace std;

class DemoScene : public Scene {
	virtual std::string get_name() const override { return "aa"; }
	void load_scene() override {
		GameObject camera = new_object("camera");
		camera.add_component<Camera>(ivec2{800, 800}, vec2{10, 10}, Camera::Data{
			.bg_color = {0x22, 0x22, 0x22},
		});


		GameObject ground = new_object("ground", "", vec2{0, 4});
		Sprite & ground_sprite = ground.add_component<Sprite>(
			Asset{"asset/texture/square.png"},
			Sprite::Data{ .size = {10, 2}, }
		);
		ground.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 1.0,
			.body_type = Rigidbody::BodyType::STATIC,
		});
		ground.add_component<BoxCollider>(ground_sprite.data.size);


		GameObject bouncy = new_object("bouncy", "", vec2{-4, 0});
		bouncy.add_component<Sprite>(
			Asset{"asset/texture/square.png"},
			Sprite::Data{
				.color = Color::GREEN,
				.size = { 1, 1 },
			}
		);
		bouncy.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 1.0,
			.linear_velocity = {1, 0},
			.elastisity_coefficient = 0.6,
		});
		bouncy.add_component<BoxCollider>(vec2{1, 1});

		GameObject stiff = new_object("stiff", "", vec2{-4, 0});
		stiff.add_component<Sprite>(
			Asset{"asset/texture/square.png"},
			Sprite::Data{
				.color = Color::RED,
				.size = { 1, 1 },
			}
		);
		stiff.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 1.0,
			.linear_velocity = {1, 0},
			.elastisity_coefficient = 0.0,
		});
		stiff.add_component<BoxCollider>(vec2{1, 1});
	}
};

int main() {
	LoopManager example;
	example.add_scene<DemoScene>();
	example.start();
	return 0;
}
