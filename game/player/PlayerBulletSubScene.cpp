#include <string>

#include "../Config.h"
#include <crepe/api/AI.h>
#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

#include "PlayerBulletScript.h"
#include "PlayerBulletSubScene.h"
#include "PlayerScript.h"
using namespace crepe;
using namespace std;
int PlayerBulletSubScene::create(Scene & scn, int counter) {
	string unique_name = "player_bullet_" + to_string(counter++);
	GameObject player_bullet
		= scn.new_object(unique_name.c_str(), "player_bullet", vec2 {0, -850}, 0, 1);

	Rigidbody & player_bullet_body = player_bullet.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 0,
		.body_type = Rigidbody::BodyType::KINEMATIC,
		.linear_velocity = vec2 {450, 0},
		.angular_velocity = 300,
		.kinematic_collision = false,
		.collision_layers = {COLL_LAY_ENEMY, COLL_LAY_ZAPPER},

		.collision_layer = COLL_LAY_PLAYER_BULLET,

	});
	player_bullet_body.active = false;
	BoxCollider & player_bullet_collider
		= player_bullet.add_component<BoxCollider>(vec2(30, 30));

	Asset player_bullet_asset {"asset/other_effects/crepe.png"};
	Sprite & player_bullet_sprite = player_bullet.add_component<Sprite>(
		player_bullet_asset,
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = SORT_IN_LAY_OBSTACLES,
			.order_in_layer = 1,
			.size = vec2(30, 0),
		}
	);
	player_bullet.add_component<BehaviorScript>().set_script<PlayerBulletScript>().active
		= false;
	return counter;
}
