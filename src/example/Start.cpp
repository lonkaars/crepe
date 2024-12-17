#include "Start.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Asset.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <iostream>

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
	begin_x += 700;

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
	obj.add_component<Animator>(lamp_glow_sprite, ivec2(422, 384), uvec2(6, 1),
								Animator::Data{
									.fps = fps,
									.looping = true,
								});
}
