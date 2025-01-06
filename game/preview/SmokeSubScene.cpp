
#include "SmokeSubScene.h"

#include "../Config.h"

#include <crepe/api/Scene.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Sprite.h>

using namespace crepe;

SmokeSubScene::SmokeSubScene(Scene & scn){
	GameObject smoke = scn.new_object("smoke_particle", "TAG", vec2 {500, -210}, 0, 1);

	Asset smoke_ss {"asset/particles/smoke.png"};

	auto & smoke_sprite = smoke.add_component<Sprite>(
		smoke_ss,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PARTICLES_FOREGROUND,
			.size = {0, 30},
		}
	);

	smoke.add_component<ParticleEmitter>(
		smoke_sprite,
		ParticleEmitter::Data {
			.offset = {0, -60},
			.max_particles = 10,
			.emission_rate = 25,
			.min_angle = 60,
			.max_angle = 120,
			.begin_lifespan = 1,
			.end_lifespan = 2,
		}
	);

}
