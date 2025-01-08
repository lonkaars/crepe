
#include "FloatingWindowSubScene.h"
#include "MenusConfig.h"

#include <crepe/api/Camera.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void FloatingWindowSubScene::create(Scene & scn, const Data & data) {
	const vec2 SIZE = {data.width, data.width * 0.75f};
	const vec2 POSITION_CORRECTION = vec2 {0, -SIZE.y / 2} + data.offset;
	const float THICKNESS_BANNER = 34;
	const float MIDDLE_OFFSET_FACTOR_TICKNESS = 0.83;
	const float MIDDLE_OFFSET_FACTOR_OFFSET = 1.2;
	const float MIDDLE_OFFSET_FACTOR_MIDDLE_WIDTH = 0.86;
	const float MIDDLE_OFFSET_OFFSET_ADDITION = -0.5;
	const float BOTTOM_OFFSET_X = 3;
	const float BOTTOM_OFFSET_Y = -3;

	GameObject floatingwindow = scn.new_object("FloatingWindow", data.group_tag);

	// Top_middle
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_middle_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {SIZE.x, THICKNESS_BANNER},
			.position_offset = POSITION_CORRECTION + vec2 {0, 0},
			.world_space = false,
		}
	);

	// Top_Left
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_left_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {THICKNESS_BANNER, THICKNESS_BANNER},
			.position_offset
			= POSITION_CORRECTION + vec2 {-SIZE.x / 2 - THICKNESS_BANNER / 2, 0},
			.world_space = false,
		}
	);

	// Top_Right
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_right_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {THICKNESS_BANNER, THICKNESS_BANNER},
			.position_offset
			= POSITION_CORRECTION + vec2 {SIZE.x / 2 + THICKNESS_BANNER / 2, 0},
			.world_space = false,
		}
	);

	// Top_middle_2
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_2_middle_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {SIZE.x, THICKNESS_BANNER},
			.position_offset = POSITION_CORRECTION + vec2 {0, THICKNESS_BANNER},
			.world_space = false,
		}
	);

	// Top_Left_2
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_2_left_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {THICKNESS_BANNER, THICKNESS_BANNER},
			.position_offset = POSITION_CORRECTION
							   + vec2 {-SIZE.x / 2 - THICKNESS_BANNER / 2, THICKNESS_BANNER},
			.world_space = false,
		}
	);

	// Top_Right_2
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_2_right_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {THICKNESS_BANNER, THICKNESS_BANNER},
			.position_offset
			= POSITION_CORRECTION + vec2 {SIZE.x / 2 + THICKNESS_BANNER / 2, THICKNESS_BANNER},
			.world_space = false,
		}
	);

	// Top_middle_3
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_3_middle_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {SIZE.x, THICKNESS_BANNER},
			.position_offset = POSITION_CORRECTION + vec2 {0, THICKNESS_BANNER * 2},
			.world_space = false,
		}
	);

	// Top_Left_3
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_3_left_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {THICKNESS_BANNER, THICKNESS_BANNER},
			.position_offset
			= POSITION_CORRECTION
			  + vec2 {-SIZE.x / 2 - THICKNESS_BANNER / 2, THICKNESS_BANNER * 2},
			.world_space = false,
		}
	);

	// Top_Right_3
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_3_right_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {THICKNESS_BANNER, THICKNESS_BANNER},
			.position_offset
			= POSITION_CORRECTION
			  + vec2 {SIZE.x / 2 + THICKNESS_BANNER / 2, THICKNESS_BANNER * 2},
			.world_space = false,
		}
	);

	// Middle_Mid
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/middle_mid_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 7,
			.size
			= {SIZE.x * MIDDLE_OFFSET_FACTOR_OFFSET * MIDDLE_OFFSET_FACTOR_MIDDLE_WIDTH
				   + data.width_middle_offset,
			   SIZE.y},
			.position_offset
			= POSITION_CORRECTION
			  + vec2 {0, THICKNESS_BANNER * 3 + SIZE.y / 2 - THICKNESS_BANNER / 2},
			.world_space = false,
		}
	);

	// Middle_Left
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/middle_left_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {THICKNESS_BANNER * MIDDLE_OFFSET_FACTOR_TICKNESS, SIZE.y},
			.position_offset
			= POSITION_CORRECTION
			  + vec2 {-SIZE.x / 2 - THICKNESS_BANNER / 2 * MIDDLE_OFFSET_FACTOR_OFFSET - MIDDLE_OFFSET_OFFSET_ADDITION, THICKNESS_BANNER * 3 + SIZE.y / 2 - THICKNESS_BANNER / 2},
			.world_space = false,
		}
	);

	// Middle_Right
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/middle_right_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size = {THICKNESS_BANNER * MIDDLE_OFFSET_FACTOR_TICKNESS, SIZE.y},
			.position_offset
			= POSITION_CORRECTION
			  + vec2 {SIZE.x / 2 + THICKNESS_BANNER / 2 * MIDDLE_OFFSET_FACTOR_OFFSET + MIDDLE_OFFSET_OFFSET_ADDITION, THICKNESS_BANNER * 3 + SIZE.y / 2 - THICKNESS_BANNER / 2},
			.world_space = false,
		}
	);

	// Bot_Middle
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/bot_middle_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 7,
			.size
			= {SIZE.x * MIDDLE_OFFSET_FACTOR_OFFSET * MIDDLE_OFFSET_FACTOR_MIDDLE_WIDTH
				   + data.width_middle_offset,
			   THICKNESS_BANNER * MIDDLE_OFFSET_FACTOR_TICKNESS},
			.position_offset
			= POSITION_CORRECTION + vec2 {0, THICKNESS_BANNER * 3 + SIZE.y + BOTTOM_OFFSET_Y},
			.world_space = false,
		}
	);

	// Bot_Left
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/bot_left_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size
			= {THICKNESS_BANNER * MIDDLE_OFFSET_FACTOR_TICKNESS,
			   THICKNESS_BANNER * MIDDLE_OFFSET_FACTOR_TICKNESS},
			.position_offset
			= POSITION_CORRECTION
			  + vec2 {-SIZE.x / 2 - THICKNESS_BANNER / 2 - BOTTOM_OFFSET_X, THICKNESS_BANNER * 3 + SIZE.y + BOTTOM_OFFSET_Y},
			.world_space = false,
		}
	);

	// Bot_Right
	floatingwindow.add_component<Sprite>(
		Asset("asset/ui/settings_container/bot_right_setting.png"),
		Sprite::Data {
			.sorting_in_layer = STARTING_SORTING_IN_LAYER + 8,
			.size
			= {THICKNESS_BANNER * MIDDLE_OFFSET_FACTOR_TICKNESS,
			   THICKNESS_BANNER * MIDDLE_OFFSET_FACTOR_TICKNESS},
			.position_offset
			= POSITION_CORRECTION
			  + vec2 {SIZE.x / 2 + THICKNESS_BANNER / 2 + BOTTOM_OFFSET_X, THICKNESS_BANNER * 3 + SIZE.y + BOTTOM_OFFSET_Y},
			.world_space = false,
		}
	);
}
