#include <string>

#include "../Config.h"
#include "EnemyConfig.h"
#include <crepe/api/AI.h>
#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

#include "../Random.h"
#include "EnemyBulletScript.h"
#include "EnemyBulletSubScene.h"
#include "EnemyScript.h"
#include "api/Color.h"
using namespace crepe;
using namespace std;
int EnemyBulletSubScene::create(Scene & scn, int counter) {
	string unique_name = "enemy_bullet_" + to_string(counter++);
	GameObject bullet = scn.new_object(
		unique_name.c_str(), "enemy_bullet", ENEMY_BULLET_POOL_LOCATION, 0, 1
	);

	Rigidbody & bullet_body = bullet.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 0,
		.body_type = Rigidbody::BodyType::KINEMATIC,
		.linear_velocity = vec2 {-300, 0},
		.kinematic_collision = false,
		.collision_layers = {COLL_LAY_MISSILE, COLL_LAY_ZAPPER},
		.collision_layer = COLL_LAY_BULLET
	});
	bullet_body.active = false;
	BoxCollider & bullet_collider = bullet.add_component<BoxCollider>(vec2(40, 10));
	//bullet_collider.active = false;
	Asset bullet_asset {"asset/other_effects/effect_smgbullet_x2.png"};
	Sprite & bullet_sprite = bullet.add_component<Sprite>(
		bullet_asset,
		Sprite::Data {
			.color = Color::BLUE,
			.flip = {true, false},
			.sorting_in_layer = SORT_IN_LAY_OBSTACLES,
			.order_in_layer = 1,
			.size = vec2(60, 0),
		}
	);
	bullet.add_component<BehaviorScript>().set_script<EnemyBulletScript>();
	return counter;
}
