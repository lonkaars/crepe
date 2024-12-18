#include "api/Asset.h"
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
					 .size = {0, 100},
					 .angle_offset = 0,
					 .position_offset = {0, 0},
				 });
		auto & emitter = game_object.add_component<ParticleEmitter>(test_sprite, ParticleEmitter::Data{});

		auto & cam = game_object.add_component<Camera>(ivec2{1280, 720}, vec2{400, 400},
													   Camera::Data{
														   .bg_color = Color::WHITE,
													   });
		cam.data.postion_offset = {1000,1000};
	}

	string get_name() const { return "TestScene"; };
};

int main(int argc, char * argv[]) {
	LoopManager engine;
	engine.add_scene<TestScene>();
	engine.start();
	return 0;
}
