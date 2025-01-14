#include "AquariumSubScene.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

float AquariumSubScene::create(Scene & scn, float begin_x) {
	this->add_background(scn, begin_x);

	GameObject aquarium_begin
		= scn.new_object("aquarium_begin", "background_aqua", vec2(begin_x, 0));
	Asset aquarium_begin_asset {"asset/background/aquarium/glassTubeFG_1_TVOS.png"};
	aquarium_begin.add_component<Sprite>(
		aquarium_begin_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 0,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 600;

	GameObject aquarium_middle_1
		= scn.new_object("aquarium_middle", "background_aqua", vec2(begin_x, 0));
	Asset aquarium_middle_1_asset {"asset/background/aquarium/glassTubeFG_3_TVOS.png"};
	aquarium_middle_1.add_component<Sprite>(
		aquarium_middle_1_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 2,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 400;

	this->add_background(scn, begin_x - 200);
	this->add_bubbles(aquarium_middle_1, vec2(-400, 300), 2, 0.7f);
	this->add_bubbles(aquarium_middle_1, vec2(-100, 300), 4, 1.0f);
	this->add_bubbles(aquarium_middle_1, vec2(500, 300), 4, 0.9f);

	GameObject aquarium_middle_2
		= scn.new_object("aquarium_middle", "background_aqua", vec2(begin_x, 0));
	Asset aquarium_middle_2_asset {"asset/background/aquarium/glassTubeFG_3_TVOS.png"};
	aquarium_middle_2.add_component<Sprite>(
		aquarium_middle_2_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 3,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 400;

	this->add_bubbles(aquarium_middle_2, vec2(300, 300), 2, 0.6f);

	GameObject aquarium_middle_3
		= scn.new_object("aquarium_middle", "background_aqua", vec2(begin_x, 0));
	Asset aquarium_middle_3_asset {"asset/background/aquarium/glassTubeFG_3_TVOS.png"};
	aquarium_middle_3.add_component<Sprite>(
		aquarium_middle_3_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 4,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 400;

	this->add_background(scn, begin_x - 200);

	GameObject aquarium_middle_4
		= scn.new_object("aquarium_middle", "background_aqua", vec2(begin_x, 0));
	Asset aquarium_middle_4_asset {"asset/background/aquarium/glassTubeFG_3_TVOS.png"};
	aquarium_middle_4.add_component<Sprite>(
		aquarium_middle_4_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 5,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 600;

	this->add_background(scn, begin_x);
	this->add_bubbles(aquarium_middle_4, vec2(175, 300), 4, 1.0f);
	this->add_bubbles(aquarium_middle_4, vec2(200, 300), 4, 0.7f);

	GameObject aquarium_end
		= scn.new_object("aquarium_end", "background_aqua", vec2(begin_x, 0));
	Asset aquarium_end_asset {"asset/background/aquarium/glassTubeFG_2_TVOS.png"};
	aquarium_end.add_component<Sprite>(
		aquarium_end_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 1,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 600;

	return begin_x;
}

void AquariumSubScene::add_background(Scene & scn, float begin_x) {
	GameObject bg_1 = scn.new_object("aquarium_bg_1", "background_aqua", vec2(begin_x, 0));
	Asset bg_1_1_asset {"asset/background/aquarium/AquariumBG1_1_TVOS.png"};
	bg_1.add_component<Sprite>(
		bg_1_1_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
			.order_in_layer = 5,
			.size = vec2(0, 400),
			.position_offset = vec2(-200, 100),
		}
	);
	Asset bg_1_2_asset {"asset/background/aquarium/AquariumBG1_2_TVOS.png"};
	bg_1.add_component<Sprite>(
		bg_1_2_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
			.order_in_layer = 5,
			.size = vec2(0, 400),
			.position_offset = vec2(200, 100),
		}
	);
	GameObject bg_2 = scn.new_object("aquarium_bg_2", "background_aqua", vec2(begin_x, 0));
	Asset bg_2_1_asset {"asset/background/aquarium/AquariumBG2_1_TVOS.png"};
	bg_2.add_component<Sprite>(
		bg_2_1_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
			.order_in_layer = 3,
			.size = vec2(0, 400),
			.position_offset = vec2(200, -50),
		}
	);
	Asset bg_2_2_asset {"asset/background/aquarium/AquariumBG2_2_TVOS.png"};
	bg_2.add_component<Sprite>(
		bg_2_2_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
			.order_in_layer = 3,
			.size = vec2(0, 400),
			.position_offset = vec2(-200, -50),
		}
	);
	GameObject bg_3 = scn.new_object("aquarium_bg_3", "background_aqua", vec2(begin_x, 0));
	Asset bg_3_1_asset {"asset/background/aquarium/AquariumBG3_1_TVOS.png"};
	bg_3.add_component<Sprite>(
		bg_3_1_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
			.order_in_layer = 1,
			.size = vec2(0, 400),
			.position_offset = vec2(200, -200),
		}
	);
	Asset bg_3_2_asset {"asset/background/aquarium/AquariumBG3_2_TVOS.png"};
	bg_3.add_component<Sprite>(
		bg_3_2_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
			.order_in_layer = 1,
			.size = vec2(0, 400),
			.position_offset = vec2(-200, -200),
		}
	);
}

void AquariumSubScene::add_bubbles(
	GameObject & obj, vec2 offset, int order_in_layer, float scale
) {
	Sprite & sprite = obj.add_component<Sprite>(
		Asset {"asset/background/aquarium/bubble.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
			.order_in_layer = order_in_layer,
			.size = vec2(0, 12.5),
			.scale_offset = scale,
		}
	);
	obj.add_component<ParticleEmitter>(
		sprite,
		ParticleEmitter::Data {
			.offset = offset,
			.max_particles = 20,
			.emission_rate = 1.2,
			.min_speed = 50,
			.max_speed = 100,
			.min_angle = 265,
			.max_angle = 275,
			.force_over_time = vec2(0, -50),
		}
	);
	Sprite & sprite_small = obj.add_component<Sprite>(
		Asset {"asset/background/aquarium/bubble.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
			.order_in_layer = order_in_layer,
			.size = vec2(0, 7.5),
			.scale_offset = scale,
		}
	);
	obj.add_component<ParticleEmitter>(
		sprite_small,
		ParticleEmitter::Data {
			.offset = offset,
			.max_particles = 20,
			.emission_rate = 0.8,
			.min_speed = 50,
			.max_speed = 100,
			.min_angle = 265,
			.max_angle = 275,
			.force_over_time = vec2(0, -50),
		}
	);
}
