#include "api/Button.h"
#include <crepe/Component.h>
#include <crepe/api/Animator.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.hpp>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/types.h>
#include <functional>
#include <iostream>

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
		Mediator & mediator = this->mediator;
		ComponentManager & mgr = mediator.component_manager;
		GameObject game_object = mgr.new_object("", "", vec2{0, 0}, 0, 1);

		Color color(255, 255, 255, 255);

		auto img = Texture("asset/spritesheet/pokemon_spritesheet.png");

		Sprite & test_sprite = game_object.add_component<Sprite>(
			img, Sprite::Data{
					 .color = color,
					 .flip = Sprite::FlipSettings{false, false},
					 .sorting_in_layer = 2,
					 .order_in_layer = 2,
					 .size = {0, 100},
					 .angle_offset = 0,
					 .position_offset = {0, 0},
				 });

		auto & anim = game_object.add_component<Animator>(test_sprite, 4, 4,
														  Animator::Data{
															  .fps = 1,
															  .looping = false,
														  });
		anim.set_anim(2);
		anim.pause();

		auto & cam = game_object.add_component<Camera>(ivec2{1280, 720}, vec2{400, 400},
													   Camera::Data{
														   .bg_color = Color::WHITE,
													   });

		function<void()> on_click = [&](){ cout << "button clicked" << std::endl; };
		function<void()> on_enter = [&](){ cout << "enter" << std::endl; };
		function<void()> on_exit = [&](){ cout << "exit" << std::endl; };

		auto & button = game_object.add_component<Button>(vec2{200,200}, vec2{0,0}, on_click, false);
		button.on_mouse_enter = on_enter;
		button.on_mouse_exit = on_exit;
		button.is_toggle = true;
		button.active = true;

	}

	string get_name() const { return "TestScene"; };
};

int main(int argc, char * argv[]) {
	LoopManager engine;
	engine.add_scene<TestScene>();
	engine.start();
	return 0;
}
