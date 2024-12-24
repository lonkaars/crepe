#include "PlayerSubScene.h"
#include "PlayerScript.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

PlayerSubScene::PlayerSubScene(Scene & scn) {
	GameObject player = scn.new_object("player", "player", vec2(-100, 200));

	Asset player_bullet {"asset/other_effects/effect_smgbullet.png"};
	Sprite & player_bullet_sprite = player.add_component<Sprite>(
		player_bullet,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 3,
			.size = vec2(0, 6),
		}
	);
	player.add_component<ParticleEmitter>(player_bullet_sprite, ParticleEmitter::Data{
		.offset = vec2(-15, 15),
		.emission_rate = 0,
		.min_speed = 300,
		.max_speed = 500,
		.min_angle = 85,
		.max_angle = 100,
		.boundary = ParticleEmitter::Boundary {
			.height = 400,
			.reset_on_exit = true,
		},
	});
	Asset player_bullet_x2 {"asset/other_effects/effect_smgbullet_x2.png"};
	Sprite & player_bullet_x2_sprite = player.add_component<Sprite>(
		player_bullet_x2,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 3,
			.size = vec2(0, 12),
		}
	);
	player.add_component<ParticleEmitter>(player_bullet_x2_sprite, ParticleEmitter::Data{
		.offset = vec2(-15, 15),
		.emission_rate = 0,
		.min_speed = 300,
		.max_speed = 500,
		.min_angle = 85,
		.max_angle = 100,
		.boundary = ParticleEmitter::Boundary {
			.height = 400,
			.reset_on_exit = true,
		},
	});
	Asset player_shell {"asset/other_effects/effect_rocketmgshell_TVOS.png"};
	Sprite & player_shell_sprite = player.add_component<Sprite>(
		player_shell,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 3,
			.size = vec2(0, 12),
			.angle_offset = 90,
		}
	);
	player.add_component<ParticleEmitter>(player_shell_sprite, ParticleEmitter::Data{
		.offset = vec2(-15, 15),
		.emission_rate = 0,
		.min_speed = 200,
		.max_speed = 500,
		.min_angle = 110,
		.max_angle = 120,
		.force_over_time = vec2(0, 1000),
		.boundary = ParticleEmitter::Boundary {
			.height = 400,
			.reset_on_exit = true,
		},
	});

	Asset player_body_asset {"asset/barry/defaultBody.png"};
	Sprite & player_body_sprite = player.add_component<Sprite>(
		player_body_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 0,
			.size = vec2(0, 50),
		}
	);
	player.add_component<Animator>(
		player_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	player.add_component<BoxCollider>(vec2(50, 50));
	Asset player_head_asset {"asset/barry/defaultHead.png"};
	Sprite & player_head_sprite = player.add_component<Sprite>(
		player_head_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 1,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	player.add_component<Animator>(
		player_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	player.add_component<CircleCollider>(25, vec2(0, -20));
	Asset player_jetpack_asset {"asset/barry/jetpackDefault.png"};
	Sprite & player_jetpack_sprite = player.add_component<Sprite>(
		player_jetpack_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 2,
			.size = vec2(0, 60),
			.position_offset = vec2(-20, 0),
		}
	);
	player_jetpack_sprite.active = false;
	player.add_component<Animator>(
		player_jetpack_sprite, ivec2(32, 44), uvec2(4, 4),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	player.add_component<BoxCollider>(vec2(40, 60), vec2(-20, 0));
	player.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(100, 0),
		.collision_layers
		= {COLL_LAY_BOT_TOP, COLL_LAY_ZAPPER, COLL_LAY_LASER, COLL_LAY_MISSILE},
		.collision_layer = COLL_LAY_PLAYER,
	});
	player.add_component<BehaviorScript>().set_script<PlayerScript>().active = false;
}
