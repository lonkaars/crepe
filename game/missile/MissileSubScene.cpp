#include "MissileSubScene.h"
#include "../Config.h"
#include "../preview/MissleScript.h"
#include "CollisionScript.h"

#include <crepe/api/AI.h>
#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/types.h>

using namespace crepe;

int MissileSubScene::create(crepe::Scene & scn) {

	GameObject missle = scn.new_object("missile", "TAG", {0, 0}, 0, 1);

	Asset missle_ss {"asset/obstacles/missile/missile.png"};
	Asset missle_thruster_ss {"asset/obstacles/missile/missileEffects.png"};
	Asset missile_explosion_ss {"asset/obstacles/missile/missileExplosion.png"};
	Asset explosion_sound {"asset/sfx/rocket_explode_1.ogg"};
	Asset missile_fire {"asset/sfx/missile_launch.ogg"};

	missle.add_component<BehaviorScript>().set_script<MissleScript>().active = false;
	missle.add_component<BehaviorScript>().set_script<MissileCollisionScript>().active = false;

	auto & sound = missle.add_component<AudioSource>(missile_fire);
	missle.add_component<AudioSource>(explosion_sound);

	// sprites
	auto & missle_sprite = missle.add_component<Sprite>(
		missle_ss,
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = SORT_IN_LAY_OBSTACLES,
			.size = {0, 35},
		}
	);

	auto & missle_thruster_sprite = missle.add_component<Sprite>(
		missle_thruster_ss,
		Sprite::Data {
			.flip = {true, false},
			.sorting_in_layer = SORT_IN_LAY_OBSTACLES,
			.size = {0, 35},
			.position_offset = {-20, 0},
		}
	);

	auto & missile_explosion_sprite = missle.add_component<Sprite>(
		missile_explosion_ss,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_OBSTACLES,
			.size = {0, 50},
		}
	);

	// Animations
	missle.add_component<Animator>(
		missle_sprite, ivec2 {32, 32}, uvec2 {4, 1},
		Animator::Data {
			.looping = true,
		}
	);

	missle.add_component<Animator>(
		missle_thruster_sprite, ivec2 {64, 64}, uvec2 {4, 2},
		Animator::Data {
			.looping = true,
		}
	);

	auto & explosion_anim = missle.add_component<Animator>(
		missile_explosion_sprite, ivec2 {64, 64}, uvec2 {8, 1}, Animator::Data {}
	);

	missile_explosion_sprite.active = false;
	explosion_anim.active = false;

	missle.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::KINEMATIC,
		.max_linear_velocity = 40,
		.kinematic_collision = false,
		.collision_layers = {COLL_LAY_PLAYER},
		.collision_layer = COLL_LAY_MISSILE,
	});

	missle.add_component<CircleCollider>(3);

	auto & missle_ai = missle.add_component<AI>(1000);

	static int missile_counter = 0;
	return missile_counter++;
}
