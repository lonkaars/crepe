#include "MissileSubScene.h"
#include "../Config.h"
#include "../preview/MissleScript.h"
#include "CollisionScript.h"
#include "api/CircleCollider.h"
#include "types.h"

#include <crepe/api/AI.h>
#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

using namespace crepe;

MissileSubScene::MissileSubScene(crepe::Scene & scn, const crepe::vec2 & start_pos) {

	GameObject missle = scn.new_object("missle", "TAG", start_pos, 0, 1);

	Asset missle_ss {"asset/obstacles/missile/missile.png"};
	Asset missle_thruster_ss {"asset/obstacles/missile/missileEffects.png"};
	Asset missile_explosion_ss {"asset/obstacles/missile/missileExplosion.png"};

	missle.add_component<BehaviorScript>().set_script<MissleScript>();
	missle.add_component<BehaviorScript>().set_script<MissileCollisionScript>();

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
		missle_thruster_sprite, ivec2 {64, 64}, uvec2 {8, 1}, Animator::Data {}
	);

	missile_explosion_sprite.active = false;
	explosion_anim.active = false;

	missle.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::KINEMATIC,
		.max_linear_velocity = 40,
		.kinematic_collision = false,
		.collision_layers = {COLL_LAY_PLAYER},
	});

	missle.add_component<CircleCollider>(2);

	auto & missle_ai = missle.add_component<AI>(1000);
}
