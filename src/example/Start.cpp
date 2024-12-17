#include "Start.h"
#include "api/Asset.h"
#include "types.h"

#include <crepe/api/Animator.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

using namespace crepe;
using namespace std;

float Start::create(Scene & scn, float begin_x) {
	GameObject begin = scn.new_object("start_begin", "background", vec2(begin_x, 0));
	Asset begin_asset{"asset/jetpack_joyride/background/start/titleFG_1_TVOS.png"};
	begin.add_component<Sprite>(begin_asset, Sprite::Data{
												 .sorting_in_layer = 4,
												 .order_in_layer = 0,
												 .size = vec2(0, 800),
											 });
	GameObject hole = scn.new_object("start_hole", "background", vec2(begin_x - 250, 140));
	Asset hole_asset{"asset/jetpack_joyride/background/start/titleWallHole.png"};
	Sprite & hole_sprite = hole.add_component<Sprite>(hole_asset, Sprite::Data{
																	  .sorting_in_layer = 4,
																	  .order_in_layer = 1,
																	  .size = vec2(0, 200),
																  });
	hole_sprite.active = false;
	begin_x += 700;

	this->add_table(begin, vec2(-150, 150));
	this->add_light(begin, vec2(-125, -150));
	this->add_jetpack_stand(begin, vec2(-125, 200));

	GameObject end = scn.new_object("start_end", "background", vec2(begin_x, 0));
	Asset end_asset{"asset/jetpack_joyride/background/start/titleFG_2_TVOS.png"};
	end.add_component<Sprite>(end_asset, Sprite::Data{
											 .sorting_in_layer = 4,
											 .order_in_layer = 1,
											 .size = vec2(0, 800),
										 });
	begin_x += 100;

	this->add_lamp(end, vec2(-350, -95));

	return begin_x;
}

void Start::add_lamp(GameObject & obj, vec2 offset, unsigned int fps) {
	Asset lamp_asset{"asset/jetpack_joyride/background/start/alarmLight_TVOS.png"};
	obj.add_component<Sprite>(lamp_asset, Sprite::Data{
											  .sorting_in_layer = 5,
											  .order_in_layer = 0,
											  .size = vec2(0, 100),
											  .position_offset = offset,
										  });
	Asset lamp_glow_asset{"asset/jetpack_joyride/background/start/alarmGlow_TVOS.png"};
	Sprite & lamp_glow_sprite = obj.add_component<Sprite>(
		lamp_glow_asset, Sprite::Data{
							 .sorting_in_layer = 5,
							 .order_in_layer = 1,
							 .size = vec2(0, 300),
							 .position_offset = offset - vec2(65, -55),
						 });
	lamp_glow_sprite.active = false;
	obj.add_component<Animator>(lamp_glow_sprite, ivec2(422, 384), uvec2(6, 1),
								Animator::Data{
									.fps = fps,
									.looping = true,
								});
}

void Start::add_table(GameObject & obj, vec2 offset) {
	Asset table_asset{"asset/jetpack_joyride/background/start/table.png"};
	obj.add_component<Sprite>(table_asset, Sprite::Data{
											   .sorting_in_layer = 5,
											   .order_in_layer = 0,
											   .size = vec2(0, 100),
											   .position_offset = offset,
										   });
	Asset gramophone_asset{"asset/jetpack_joyride/background/start/gramophone_TVOS.png"};
	Sprite & gramophone_sprite = obj.add_component<Sprite>(
		gramophone_asset, Sprite::Data{
							  .sorting_in_layer = 5,
							  .order_in_layer = 1,
							  .size = vec2(0, 100),
							  .position_offset = offset + vec2(0, -50),
						  });
	obj.add_component<Animator>(gramophone_sprite, ivec2(64, 128), uvec2(2, 1),
								Animator::Data{
									.fps = 10,
									.looping = true,
								});
}

void Start::add_light(crepe::GameObject & obj, crepe::vec2 offset) {
	Asset light_asset{"asset/jetpack_joyride/background/start/title_light_TVOS.png"};
	obj.add_component<Sprite>(light_asset, Sprite::Data{
											   .sorting_in_layer = 5,
											   .order_in_layer = 0,
											   .size = vec2(0, 200),
											   .position_offset = offset,
										   });
	Asset light_glow_asset{"asset/jetpack_joyride/background/start/lightEffect2.png"};
	obj.add_component<Sprite>(light_glow_asset, Sprite::Data{
													.sorting_in_layer = 5,
													.order_in_layer = 1,
													.size = vec2(0, 100),
													.position_offset = offset + vec2(0, 75),
												});
	Asset light_effect_asset{"asset/jetpack_joyride/background/start/lightEffect.png"};
	obj.add_component<Sprite>(light_effect_asset, Sprite::Data{
													  .sorting_in_layer = 5,
													  .order_in_layer = 0,
													  .size = vec2(0, 100),
													  .position_offset = offset + vec2(0, 350),
												  });
}

void Start::add_jetpack_stand(crepe::GameObject & obj, crepe::vec2 offset) {
	Asset jetpack_stand_asset{"asset/jetpack_joyride/background/start/JetpackStand.png"};
	Sprite & jetpeck_stand_sprite
		= obj.add_component<Sprite>(jetpack_stand_asset, Sprite::Data{
															 .sorting_in_layer = 5,
															 .order_in_layer = 1,
															 .size = vec2(0, 70),
															 .position_offset = offset,
														 });
	obj.add_component<Animator>(jetpeck_stand_sprite, ivec2(34, 46), uvec2(2, 1),
								Animator::Data{
									.fps = 10,
									.looping = true,
								})
		.pause();
	Asset do_not_steal = {"asset/jetpack_joyride/background/start/doNotTouchSign_TVOS.png"};
	obj.add_component<Sprite>(do_not_steal, Sprite::Data{
												.sorting_in_layer = 5,
												.order_in_layer = 1,
												.size = vec2(0, 100),
												.position_offset = offset + vec2(-75, -25),
											});
}
