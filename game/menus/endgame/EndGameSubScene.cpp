
#include "EndGameSubScene.h"

#include "../MenusConfig.h"
#include "../../Config.h"
#include "api/GameObject.h"
#include "api/Scene.h"
#include "api/Sprite.h"

#include <crepe/api/Camera.h>

using namespace crepe;
using namespace std;

void EndGameSubScene::create(Scene & scn){
	const vec2 SIZE = {200,100};
	const float THICKNESS_BANNER = 34;
	const float MIDDLE_OFFSET_FACTOR_TICKNESS = 0.83;
	const float MIDDLE_OFFSET_FACTOR_OFFSET = 1.2;
	const float MIDDLE_OFFSET_TICKNESS_ADDITION = -8;
	const float MIDDLE_OFFSET_OFFSET_ADDITION = -0.5;
	const float BOTTOM_OFFSET_X = 3;
	const float BOTTOM_OFFSET_Y = -5;

	GameObject endgame = scn.new_object("EndGameSubScene");

	// Top_middle
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_middle_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {SIZE.x,THICKNESS_BANNER},
		.position_offset = {0,0},
		});

	// Top_Left
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_left_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER,THICKNESS_BANNER},
		.position_offset = {-SIZE.x/2-THICKNESS_BANNER/2,0},
		});

	// Top_Right
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_right_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER,THICKNESS_BANNER},
		.position_offset = {SIZE.x/2+THICKNESS_BANNER/2,0},
		});

	// Top_middle_2
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_2_middle_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {SIZE.x,THICKNESS_BANNER},
		.position_offset = {0,THICKNESS_BANNER},
		});

	// Top_Left_2
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_2_left_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER,THICKNESS_BANNER},
		.position_offset = {-SIZE.x/2-THICKNESS_BANNER/2,THICKNESS_BANNER},
		});

	// Top_Right_2
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_2_right_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER,THICKNESS_BANNER},
		.position_offset = {SIZE.x/2+THICKNESS_BANNER/2,THICKNESS_BANNER},
		});

	// Top_middle_3
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_3_middle_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {SIZE.x,THICKNESS_BANNER},
		.position_offset = {0,THICKNESS_BANNER*2},
		});

	// Top_Left_3
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_3_left_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER,THICKNESS_BANNER},
		.position_offset = {-SIZE.x/2-THICKNESS_BANNER/2,THICKNESS_BANNER*2},
		});

	// Top_Right_3
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/top_3_right_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER,THICKNESS_BANNER},
		.position_offset = {SIZE.x/2+THICKNESS_BANNER/2,THICKNESS_BANNER*2},
		});

	// Middle_Mid
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/middle_mid_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+7,
		.size = {SIZE.x*MIDDLE_OFFSET_FACTOR_OFFSET+MIDDLE_OFFSET_TICKNESS_ADDITION,SIZE.y},
		.position_offset = {0,THICKNESS_BANNER*3+SIZE.y/2-THICKNESS_BANNER/2},
		});

	// Middle_Left
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/middle_left_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER*MIDDLE_OFFSET_FACTOR_TICKNESS,SIZE.y},
		.position_offset = {-SIZE.x/2-THICKNESS_BANNER/2*MIDDLE_OFFSET_FACTOR_OFFSET-MIDDLE_OFFSET_OFFSET_ADDITION,THICKNESS_BANNER*3+SIZE.y/2-THICKNESS_BANNER/2},
		});

	// Middle_Right
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/middle_right_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER*MIDDLE_OFFSET_FACTOR_TICKNESS,SIZE.y},
		.position_offset = {SIZE.x/2+THICKNESS_BANNER/2*MIDDLE_OFFSET_FACTOR_OFFSET+MIDDLE_OFFSET_OFFSET_ADDITION,THICKNESS_BANNER*3+SIZE.y/2-THICKNESS_BANNER/2},
		});

	// Bot_Middle
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/bot_middle_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+7,
		.size = {SIZE.x*MIDDLE_OFFSET_FACTOR_OFFSET+MIDDLE_OFFSET_TICKNESS_ADDITION,THICKNESS_BANNER*MIDDLE_OFFSET_FACTOR_TICKNESS},
		.position_offset = {0,THICKNESS_BANNER*3+SIZE.y-5},
		});

	// Bot_Left
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/bot_left_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER*MIDDLE_OFFSET_FACTOR_TICKNESS,THICKNESS_BANNER*MIDDLE_OFFSET_FACTOR_TICKNESS},
		.position_offset = {-SIZE.x/2-THICKNESS_BANNER/2-BOTTOM_OFFSET_X,THICKNESS_BANNER*3+SIZE.y+BOTTOM_OFFSET_Y},
		});

	// Bot_Right
	endgame.add_component<Sprite>(
		Asset("asset/ui/settings_container/bot_right_setting.png"),
		Sprite::Data{
		.sorting_in_layer = STARTING_SORTING_IN_LAYER+8,
		.size = {THICKNESS_BANNER*MIDDLE_OFFSET_FACTOR_TICKNESS,THICKNESS_BANNER*MIDDLE_OFFSET_FACTOR_TICKNESS},
		.position_offset = {SIZE.x/2+THICKNESS_BANNER/2+BOTTOM_OFFSET_X,THICKNESS_BANNER*3+SIZE.y+BOTTOM_OFFSET_Y},
		});
}


