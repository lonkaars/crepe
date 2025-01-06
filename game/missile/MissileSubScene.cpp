#include "MissileSubScene.h"
#include "../preview/MissleScript.h"

#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/AI.h>

using namespace crepe;

MissileSubScene::MissileSubScene(Scene & scn){

	GameObject missle = scn.new_object("missle", "TAG", vec2 {0, 0}, 0, 1);
	Asset missle_ss {"asset/obstacles/missile/missile.png"};
	missle.add_component<BehaviorScript>().set_script<MissleScript>();
	auto & missle_sprite = missle.add_component<Sprite>(
		missle_ss,
		Sprite::Data {
			.sorting_in_layer = 10,
			.size = {0, 35},
		}
	);

	missle.add_component<Animator>(
		missle_sprite, ivec2 {32, 32}, uvec2 {4, 1},
		Animator::Data {
			.looping = true,
		}
	);
	missle.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.max_linear_velocity = 40,
	});

	auto & missle_ai = missle.add_component<AI>(1000);
}
