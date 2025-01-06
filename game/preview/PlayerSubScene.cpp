
#include "PlayerSubScene.h"

#include "PlayerScript.h"

#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/AudioSource.h>

#include <crepe/ValueBroker.h>
#include <crepe/manager/SaveManager.h>

using namespace crepe;

PlayerSubScene::PlayerSubScene(Scene & scn) {
	auto & savemgr = scn.get_save_manager();

	ValueBroker player_x = savemgr.get<float>("player_x", 750);
	ValueBroker player_y = savemgr.get<float>("player_y", 0);

	GameObject player
		= scn.new_object("player", "TAG", vec2 {player_x.get(), player_y.get()}, 0, 1);

	Asset player_body {"asset/Barry/defaultBody.png"};
	Asset player_head {"asset/Barry/defaultHead.png"};

	auto & player_head_sprite = player.add_component<Sprite>(
		player_head,
		Sprite::Data {
			.sorting_in_layer = 1,
			.order_in_layer = 1,
			.size = vec2 {0, 100},
		}
	);
	auto & player_head_anim = player.add_component<Animator>(
		player_head_sprite, ivec2 {32, 32}, uvec2 {4, 8}, Animator::Data {}
	);
	player_head_anim.loop();

	auto & player_body_sprite = player.add_component<Sprite>(
		player_body,
		Sprite::Data {
			.sorting_in_layer = 1,
			.order_in_layer = 0,
			.size = vec2 {0, 100},
			.position_offset = vec2 {0, 40},
		}
	);
	auto & player_body_anim = player.add_component<Animator>(
		player_body_sprite, ivec2 {32, 32}, uvec2 {4, 8}, Animator::Data {}
	);
	player_body_anim.loop();

	player.add_component<BehaviorScript>().set_script<PlayerScript>();
	player.add_component<BoxCollider>(vec2 {50, 100});

	player.add_component<Rigidbody>(Rigidbody::Data {
		.mass = 10,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = {0, 0},
		.constraints = {0, 0, 0},
		.elasticity_coefficient = 0,
		.collision_layers = {0},
	});
}
