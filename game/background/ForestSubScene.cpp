#include "ForestSubScene.h"
#include "ForestParallaxScript.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

float ForestSubScene::create(Scene & scn, float begin_x, std::string unique_bg_name) {
	GameObject script = scn.new_object("forest_script", "background");
	script.add_component<BehaviorScript>().set_script<ForestParallaxScript>(
		begin_x - 400, begin_x + 3000 + 400, unique_bg_name);

	this->add_background(scn, begin_x, unique_bg_name);

	GameObject begin = scn.new_object("forest_begin", "background", vec2(begin_x, 0));
	Asset begin_asset{"asset/background/forest/forestFG_1_TVOS.png"};
	begin.add_component<Sprite>(begin_asset, Sprite::Data{
												 .sorting_in_layer = SORT_IN_LAY_BACKGROUND,
												 .order_in_layer = 0,
												 .size = vec2(0, 800),
											 });
	begin_x += 800;

	this->add_background(scn, begin_x, unique_bg_name);

	GameObject middle_1 = scn.new_object("forest_middle", "background", vec2(begin_x, 0));
	Asset middle_1_asset{"asset/background/forest/forestFG_3_TVOS.png"};
	middle_1.add_component<Sprite>(middle_1_asset,
								   Sprite::Data{
									   .sorting_in_layer = SORT_IN_LAY_BACKGROUND,
									   .order_in_layer = 2,
									   .size = vec2(0, 800),
								   });
	begin_x += 800;

	this->add_background(scn, begin_x, unique_bg_name);

	GameObject middle_2 = scn.new_object("forest_middle", "background", vec2(begin_x, 0));
	Asset middle_2_asset{"asset/background/forest/forestFG_3_TVOS.png"};
	middle_2.add_component<Sprite>(middle_2_asset,
								   Sprite::Data{
									   .sorting_in_layer = SORT_IN_LAY_BACKGROUND,
									   .order_in_layer = 3,
									   .size = vec2(0, 800),
								   });
	begin_x += 800;

	this->add_background(scn, begin_x, unique_bg_name);

	GameObject end = scn.new_object("forest_end", "background", vec2(begin_x, 0));
	Asset end_asset{"asset/background/forest/forestFG_2_TVOS.png"};
	end.add_component<Sprite>(end_asset, Sprite::Data{
											 .sorting_in_layer = SORT_IN_LAY_BACKGROUND,
											 .order_in_layer = 1,
											 .size = vec2(0, 800),
										 });
	begin_x += 600;

	this->add_background(scn, begin_x + 200, unique_bg_name);

	return begin_x;
}

void ForestSubScene::add_background(Scene & scn, float begin_x, std::string name) {
	GameObject bg_1
		= scn.new_object("forest_bg_1_" + name, "forest_background", vec2(begin_x, 0));
	Asset bg_1_asset{"asset/background/forest/forestBG1_1_TVOS.png"};
	bg_1.add_component<Sprite>(bg_1_asset, Sprite::Data{
											   .sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
											   .order_in_layer = 2,
											   .size = vec2(0, 800),
										   });
	GameObject bg_2
		= scn.new_object("forest_bg_2_" + name, "forest_background", vec2(begin_x, 0));
	Asset bg_2_1_asset{"asset/background/forest/forestBG2_1_TVOS.png"};
	bg_2.add_component<Sprite>(bg_2_1_asset,
							   Sprite::Data{
								   .sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
								   .order_in_layer = 1,
								   .size = vec2(0, 400),
								   .position_offset = vec2(200, 0),
							   });
	Asset bg_2_2_asset{"asset/background/forest/forestBG2_2_TVOS.png"};
	bg_2.add_component<Sprite>(bg_2_2_asset,
							   Sprite::Data{
								   .sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
								   .order_in_layer = 1,
								   .size = vec2(0, 400),
								   .position_offset = vec2(-200, 0),
							   });
	GameObject bg_3
		= scn.new_object("forest_bg_3_" + name, "forest_background", vec2(begin_x, 0));
	Asset bg_3_1_asset{"asset/background/forest/forestBG3_1_TVOS.png"};
	bg_3.add_component<Sprite>(bg_3_1_asset,
							   Sprite::Data{
								   .sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
								   .order_in_layer = 0,
								   .size = vec2(0, 200),
								   .position_offset = vec2(300, 0),
							   });
	Asset bg_3_2_asset{"asset/background/forest/forestBG3_2_TVOS.png"};
	bg_3.add_component<Sprite>(bg_3_2_asset,
							   Sprite::Data{
								   .sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
								   .order_in_layer = 0,
								   .size = vec2(0, 200),
								   .position_offset = vec2(100, 0),
							   });
	Asset bg_3_3_asset{"asset/background/forest/forestBG3_3_TVOS.png"};
	bg_3.add_component<Sprite>(bg_3_3_asset,
							   Sprite::Data{
								   .sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
								   .order_in_layer = 0,
								   .size = vec2(0, 200),
								   .position_offset = vec2(-100, 0),
							   });
	Asset bg_3_4_asset{"asset/background/forest/forestBG3_4_TVOS.png"};
	bg_3.add_component<Sprite>(bg_3_4_asset,
							   Sprite::Data{
								   .sorting_in_layer = SORT_IN_LAY_BACK_BACKGROUND,
								   .order_in_layer = 0,
								   .size = vec2(0, 200),
								   .position_offset = vec2(-300, 0),
							   });

	bg_2.add_component<Rigidbody>(Rigidbody::Data{
		.linear_velocity = vec2(30, 0),
	});
	bg_3.add_component<Rigidbody>(Rigidbody::Data{
		.linear_velocity = vec2(40, 0),
	});
}
