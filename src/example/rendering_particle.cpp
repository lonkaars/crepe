

#include "api/Asset.h"
#include "api/Text.h"
#include <crepe/Component.h>
#include <crepe/api/Animator.h>
#include <crepe/api/Button.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.hpp>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

/*
	auto & test = game_object.add_component<ParticleEmitter>(ParticleEmitter::Data{
		.position = {0, 0},
		.max_particles = 10,
		.emission_rate = 0.1,
		.min_speed = 6,
		.max_speed = 20,
		.min_angle = -20,
		.max_angle = 20,
		.begin_lifespan = 0,
		.end_lifespan = 60,
		.force_over_time = vec2{0, 0},
		.boundary{
			.width = 1000,
			.height = 1000,
			.offset = vec2{0, 0},
			.reset_on_exit = false,
		},
		.sprite = test_sprite,
	});
	*/

class TestScene : public Scene {
public:
	void load_scene() {
		GameObject game_object = new_object("", "", vec2{0, 0}, 0, 1);

		Color color(255, 255, 255, 255);

		Asset img{"asset/spritesheet/spritesheet_test.png"};

		Sprite & test_sprite = game_object.add_component<Sprite>(
			img, Sprite::Data{
					 .color = color,
					 .flip = Sprite::FlipSettings{false, false},
					 .sorting_in_layer = 2,
					 .order_in_layer = 2,
					 .size = {0, 0},
					 .angle_offset = 0,
					 .position_offset = {0, 0},
				 });

		auto & cam = game_object.add_component<Camera>(ivec2{1280, 720}, vec2{400, 400},
													   Camera::Data{
														   .bg_color = Color::WHITE,
													   });
		game_object.add_component<Text>(vec2{400, 400}, vec2{0, 0}, "ComicSansMS",
										Text::Data{.text_color = Color::RED}, "TEST test");
	}

	string get_name() const { return "TestScene"; };
};

int main(int argc, char * argv[]) {
	LoopManager engine;
	engine.add_scene<TestScene>();
	engine.start();
	return 0;
}
