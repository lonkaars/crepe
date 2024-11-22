#include "api/Animator.h"
#include "api/Camera.h"
#include "system/AnimatorSystem.h"
#include "system/ParticleSystem.h"
#include <SDL2/SDL_timer.h>
#include <crepe/ComponentManager.h>

#include <crepe/Component.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <crepe/system/RenderSystem.h>

#include <chrono>
#include <memory>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	ComponentManager mgr;
	GameObject game_object = mgr.new_object("", "", Vector2{1000, 500}, 0, 1);
	RenderSystem sys{mgr};
	ParticleSystem psys{mgr};
	AnimatorSystem asys{mgr};

	Color color(255, 255, 255, 255);

	Sprite & test_sprite = game_object.add_component<Sprite>(
		make_shared<Texture>("asset/spritesheet/spritesheet_test.png"), color,
		FlipSettings{true, true});
	test_sprite.order_in_layer = 5;
	test_sprite.width = 1000;
	test_sprite.height = 500;

	game_object.add_component<Animator>(test_sprite, 4, 1, 0).active = true;

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
		.force_over_time = Vector2{0, 0},
		.boundary{
			.width = 1000,
			.height = 1000,
			.offset = Vector2{0, 0},
			.reset_on_exit = false,
		},
		.sprite = test_sprite,
	});
	*/

	game_object.add_component<Camera>(Color::WHITE);

	/*
	game_object
		.add_component<Sprite>(make_shared<Texture>("asset/texture/img.png"), color,
							   FlipSettings{false, false})
		.order_in_layer
		= 6;
	*/

	auto start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		psys.update();
		asys.update();
		sys.update();
		SDL_Delay(10);
	}

	return 0;
}
