#include <string>

#include <crepe/api/AI.h>
#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

#include "../Config.h"
#include "EnemyConfig.h"
#include "EnemyScript.h"
#include "EnemySubScene.h"
using namespace crepe;
using namespace std;
//#TODO add sound
int EnemySubScene::create(Scene & scn, int enemy_counter) {

	string unique_name = "enemy_" + to_string(enemy_counter++);
	GameObject enemy = scn.new_object(unique_name.c_str(), "enemy", ENEMY_POOL_LOCATION, 0, 1);

	enemy.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 0,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.max_linear_velocity = 400,
		.collision_layers = {COLL_LAY_BOT_TOP, COLL_LAY_PLAYER_BULLET},
		.collision_layer = COLL_LAY_ENEMY,

	});
	Asset enemy_body_asset {"asset/workers/worker2Body.png"};
	enemy.add_component<BoxCollider>(vec2(50, 50));
	Sprite & enemy_body_sprite = enemy.add_component<Sprite>(
		enemy_body_asset,
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = SORT_IN_LAY_WORKERS_FRONT,
			.order_in_layer = 0,
			.size = vec2(0, 50),
		}
	);
	Animator & body_animator = enemy.add_component<Animator>(
		enemy_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = 5,
			.col = 1,
			.row = 0,
			.looping = false,
		}
	);
	body_animator.pause();
	enemy.add_component<BoxCollider>(vec2(40, 60), vec2(-20, 0));
	Asset enemy_head_asset {"asset/workers/worker2Head.png"};
	Sprite & enemy_head_sprite = enemy.add_component<Sprite>(
		enemy_head_asset,
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = SORT_IN_LAY_WORKERS_FRONT,
			.order_in_layer = 1,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	enemy.add_component<Animator>(
		enemy_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	enemy.add_component<CircleCollider>(25, vec2(0, -20));
	Asset enemy_jetpack_asset {"asset/barry/jetpackDefault.png"};
	Sprite & enemy_jetpack_sprite = enemy.add_component<Sprite>(
		enemy_jetpack_asset,
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = SORT_IN_LAY_WORKERS_FRONT,
			.order_in_layer = 2,
			.size = vec2(0, 60),
			.position_offset = vec2(20, 0),
		}
	);
	enemy_jetpack_sprite.active = true;
	enemy.add_component<Animator>(
		enemy_jetpack_sprite, ivec2(32, 44), uvec2(4, 4),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	enemy.add_component<AudioSource>(Asset("asset/sfx/bike_gun_2.ogg")).volume = 0.1;
	AI & ai_component = enemy.add_component<AI>(3000);
	ai_component.path_follow_on();
	BehaviorScript & enemy_script
		= enemy.add_component<BehaviorScript>().set_script<EnemyScript>();
	enemy_script.active = false;
	return enemy_counter;
}
