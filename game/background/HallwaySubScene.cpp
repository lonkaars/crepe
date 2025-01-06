#include "HallwaySubScene.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

using namespace crepe;
using namespace std;

float HallwaySubScene::create(
	Scene & scn, float begin_x, unsigned int sector_num, Color sector_color
) {
	GameObject begin = scn.new_object("hallway_begin", "background", vec2(begin_x, 0));
	Asset begin_asset {"asset/background/hallway/hallway1FG_1_TVOS.png"};
	begin.add_component<Sprite>(
		begin_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 0,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 600;

	this->add_sector_number(begin, vec2(-200, 0), sector_num, sector_color);
	this->add_lamp(begin, vec2(330, -120), 11);
	this->add_lamp(begin, vec2(430, -120), 9);

	GameObject middle_1 = scn.new_object("hallway_middle", "background", vec2(begin_x, 0));
	Asset middle_asset {"asset/background/hallway/hallway1FG_2_TVOS.png"};
	middle_1.add_component<Sprite>(
		middle_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 2,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 600;

	GameObject middle_2 = scn.new_object("hallway_middle", "background", vec2(begin_x, 0));
	Asset middle_asset_2 {"asset/background/hallway/hallway1FG_2_TVOS.png"};
	middle_2.add_component<Sprite>(
		middle_asset_2,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 3,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 200;

	GameObject middle_3 = scn.new_object("hallway_middle", "background", vec2(begin_x, 0));
	Asset middle_asset_3 {"asset/background/hallway/hallway1FG_2_TVOS.png"};
	middle_3.add_component<Sprite>(
		middle_asset_3,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 4,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 400;

	this->add_lamp(middle_3, vec2(0, -120));

	GameObject middle_4 = scn.new_object("hallway_middle", "background", vec2(begin_x, 0));
	Asset middle_asset_4 {"asset/background/hallway/hallway1FG_2_TVOS.png"};
	middle_4.add_component<Sprite>(
		middle_asset_4,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 5,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 600;

	GameObject end = scn.new_object("hallway_end", "background", vec2(begin_x, 0));
	Asset end_asset {"asset/background/hallway/hallway1FG_1_TVOS.png"};
	end.add_component<Sprite>(
		end_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
			.order_in_layer = 1,
			.size = vec2(0, GAME_HEIGHT),
		}
	);
	begin_x += 600;

	return begin_x;
}

void HallwaySubScene::add_lamp(GameObject & obj, vec2 offset, unsigned int fps) {
	Asset lamp_asset {"asset/background/hallway/alarmLight_TVOS.png"};
	obj.add_component<Sprite>(
		lamp_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
			.order_in_layer = 0,
			.size = vec2(0, 100),
			.position_offset = offset,
		}
	);
	Asset lamp_glow_asset {"asset/background/hallway/alarmGlow_TVOS.png"};
	Sprite & lamp_glow_sprite = obj.add_component<Sprite>(
		lamp_glow_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
			.order_in_layer = 1,
			.size = vec2(0, 300),
			.position_offset = offset - vec2(65, -30),
		}
	);
	obj.add_component<Animator>(
		lamp_glow_sprite, ivec2(422, 384), uvec2(6, 1),
		Animator::Data {
			.fps = fps,
			.looping = true,
		}
	);
}

void HallwaySubScene::add_sector_number(
	GameObject & obj, vec2 offset, unsigned int sector_num, Color sector_color
) {
	Asset sector_text_asset {"asset/background/hallway/sectorText_TVOS.png"};
	obj.add_component<Sprite>(
		sector_text_asset,
		Sprite::Data {
			.color = sector_color,
			.sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
			.order_in_layer = 0,
			.size = vec2(0, 100),
			.position_offset = offset,
		}
	);
	Asset sector_num_asset {"asset/background/hallway/sectorNumbers_TVOS.png"};
	Sprite & sector_num_sprite = obj.add_component<Sprite>(
		sector_num_asset,
		Sprite::Data {
			.color = sector_color,
			.sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
			.order_in_layer = 0,
			.size = vec2(0, 100),
			.position_offset = offset + vec2(200, 0),
		}
	);
	Animator & sector_num_anim = obj.add_component<Animator>(
		sector_num_sprite, ivec2(256, 128), uvec2(4, 4), Animator::Data {}
	);
	int column = (sector_num - 1) / 4;
	int row = (sector_num - 1) % 4;
	sector_num_anim.set_anim(column);
	for (int i = 0; i < row; i++) {
		sector_num_anim.next_anim();
	}
	sector_num_anim.pause();
}
