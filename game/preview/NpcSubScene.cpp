

#include "NpcSubScene.h"

#include "NpcScript.h"
#include "../Config.h"

#include <crepe/ValueBroker.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/manager/SaveManager.h>

using namespace crepe;

NpcSubScene::NpcSubScene(Scene & scn) {
	auto & savemgr = scn.get_save_manager();
	ValueBroker npc_x = savemgr.get<float>("npc_x", 500);
	ValueBroker npc_y = savemgr.get<float>("npc_y", 0);

	GameObject npc = scn.new_object("npc", "npc_tag", vec2 {npc_x.get(), npc_y.get()}, 0, 1);
	Asset npc_body {"asset/workers/worker1Body.png"};
	Asset npc_head {"asset/workers/worker1Head.png"};

	auto & npc_body_sprite = npc.add_component<Sprite>(
		npc_body,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.size = {0, 50},
		}
	);
	auto & npc_head_sprite = npc.add_component<Sprite>(
		npc_head,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.size = {0, 50},
			.position_offset = {0,-20},
		}
	);

	npc.add_component<Animator>(
		npc_body_sprite, ivec2 {32, 32}, uvec2 {4, 8},
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	npc.add_component<Animator>(
		npc_head_sprite, ivec2 {32, 32}, uvec2 {4, 8},
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	npc.add_component<BoxCollider>(vec2 {50, 50});

	npc.add_component<Rigidbody>(Rigidbody::Data {
		.mass = 10,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = {-50, 0},
		//.max_linear_velocity = 40,
		.collision_layers = {COLL_LAY_BOT_TOP, COLL_LAY_PLAYER},
		.collision_layer = COLL_LAY_PLAYER,
	});

	npc.add_component<BehaviorScript>().set_script<NpcScript>();
}
