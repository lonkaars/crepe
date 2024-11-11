#include "api/Camera.h"
#include "system/ParticleSystem.h"
#include <SDL2/SDL_timer.h>
#include <crepe/ComponentManager.h>

#include <crepe/Component.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/util/log.h>
#include <crepe/api/Color.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Vector2.h>

#include <chrono>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	GameObject game_object(0, "", "", Vector2{100, 100}, 0, 0.1);
	Color color(0, 0, 0, 0);
	Sprite test_sprite = game_object.add_component<Sprite>(
		make_shared<Texture>("../asset/texture/img.png"), color,
		FlipSettings{false, false});
	game_object.add_component<ParticleEmitter>(ParticleEmitter::Data{
		.position = {0, 0},
		.max_particles = 10,
		.emission_rate = 0.5,
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
	game_object.add_component<Camera>(Color::get_white());

	auto & sys = crepe::RenderSystem::get_instance();
	auto sys_part = crepe::ParticleSystem();
	auto start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		sys_part.update();
		sys.update();
		SDL_Delay(10 );
	}

	return 0;
}

