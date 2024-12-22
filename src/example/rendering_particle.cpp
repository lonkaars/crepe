

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

		Asset img {"asset/texture/square.png"};

		Sprite & test_sprite = game_object.add_component<Sprite>(
			img,
			Sprite::Data {
				.color = color,
				.flip = Sprite::FlipSettings {false, false},
				.sorting_in_layer = 2,
				.order_in_layer = 2,
				.size = {1, 1},
				.angle_offset = 0,
				.position_offset = {0, 1},
				.world_space = false,
			}
		);
		//auto & emitter			= game_object.add_component<ParticleEmitter>(test_sprite, ParticleEmitter::Data{});

		Sprite & test_sprite1 = game_object.add_component<Sprite>(
			img,
			Sprite::Data {
				.color = color,
				.size = {1, 1},
				.position_offset = {0, -1},
				.world_space = false,
			}
		);

		auto & cam = game_object.add_component<Camera>(
			ivec2 {1280, 720}, vec2 {5, 5},
			Camera::Data {
				.bg_color = Color::WHITE,
				.postion_offset = {1000, 1000},
			}
		);

		game_object.add_component<Text>(vec2{1, 1}, vec2{0, -1}, "ComicSansMS",
										Text::Data{
											.text_color = Color::RED,
										},
										"test TEST");

		game_object
			.add_component<Text>(vec2{1, 1}, vec2{0, 1}, "Ariel",
								 Text::Data{
									 .text_color = Color::BLACK,
								 },
								 "TEST test")
			.world_space
			= true;
	}

	string get_name() const { return "TestScene"; };
};

int main(int argc, char * argv[]) {
	Engine engine;
	engine.add_scene<TestScene>();
	engine.main();
	return 0;
}
