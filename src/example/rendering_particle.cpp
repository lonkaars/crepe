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
#include <crepe/system/RenderSystem.h>
#include <crepe/types.h>

#include <chrono>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	ComponentManager mgr;
	GameObject game_object = mgr.new_object("", "", vec2{0, 0}, 0, 1);
	RenderSystem sys{mgr};
	ParticleSystem psys{mgr};
	AnimatorSystem asys{mgr};

	Color color(255, 255, 255, 255);

	auto img = Texture("asset/texture/test_ap43.png");
	Sprite & test_sprite = game_object.add_component<Sprite>(
		img, color, Sprite::FlipSettings{true, true}, 1, 1, 500);

	//game_object.add_component<Animator>(test_sprite, 4, 1, 0).active = true;
	game_object.add_component<Animator>(test_sprite, 1, 1, 0).active = true;

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

	auto & cam = game_object.add_component<Camera>(Color::WHITE, ivec2{1080, 720},
												   ivec2{2000, 2000}, 1.0f);

	/*
	game_object
		.add_component<Sprite>(make_shared<Texture>("asset/texture/img.png"), color,
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
