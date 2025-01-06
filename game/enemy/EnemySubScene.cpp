#include <string>

#include "EnemySubScene.h"
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Animator.h>
#include <crepe/api/Sprite.h>
#include "../Config.h"
using namespace crepe;
using namespace std;
int EnemySubScene::create(Scene & scn){
	vec2 size = {20, 20};

	static int coin_counter = 0;
	string unique_name = "enemy_" + to_string(coin_counter++);
	GameObject enemy = scn.new_object(unique_name.c_str(),"enemy",vec2{650,0},0,1);
	enemy.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 0,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		// .collision_layers
		// = {COLL_LAY_BOT_TOP, COLL_LAY_ZAPPER, COLL_LAY_LASER},
		.collision_layer = COLL_LAY_PLAYER,
	});
	Asset enemy_body_asset {"asset/worker/worker1body.png"};
	enemy.add_component<BoxCollider>(vec2(50, 50));
	Sprite & enemy_body_sprite = enemy.add_component<Sprite>(
		enemy_body_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 0,
			.size = vec2(0, 50),
		}
	);
	enemy.add_component<BoxCollider>(vec2(40, 60), vec2(-20, 0));
	Asset enemy_head_asset {"asset/workers/worker1Head.png"};
	Sprite & enemy_head_sprite = enemy.add_component<Sprite>(
		enemy_head_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
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
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 2,
			.size = vec2(0, 60),
			.position_offset = vec2(-20, 0),
		}
	);
	enemy_jetpack_sprite.active = false;
	enemy.add_component<Animator>(
		enemy_jetpack_sprite, ivec2(32, 44), uvec2(4, 4),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	return coin_counter;
}
