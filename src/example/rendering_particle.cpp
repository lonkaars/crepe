

#include "api/Asset.h"
#include "api/Text.h"
#include <crepe/Component.h>
#include <crepe/api/Animator.h>
#include <crepe/api/Button.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Engine.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

class TestScene : public Scene {
public:
	void load_scene() {
		GameObject game_object = new_object("", "", vec2 {0, 0}, 0, 1);

		Color color(255, 255, 255, 255);

		Asset img {"asset/spritesheet/pokemon_spritesheet.png"};

		Sprite & test_sprite = game_object.add_component<Sprite>(
			img,
			Sprite::Data {
				.color = color,
				.flip = Sprite::FlipSettings {false, false},
				.sorting_in_layer = 2,
				.order_in_layer = 2,
				.size = {1, 0},
				.angle_offset = 0,
				.position_offset = {0, 1},
				.world_space = false,
			}
		);

		game_object.add_component<Animator>(
			test_sprite, ivec2 {56, 56}, uvec2 {4, 4},
			Animator::Data {
				.looping = false,
			}
		);

		auto & cam = game_object.add_component<Camera>(
			ivec2 {1280, 720}, vec2 {5, 5},
			Camera::Data {
				.bg_color = Color::WHITE,
				.postion_offset = {1000, 1000},
			}
		);
	}

	string get_name() const { return "TestScene"; };
};

int main(int argc, char * argv[]) {
	Engine engine;
	engine.add_scene<TestScene>();
	engine.main();
	return 0;
}
