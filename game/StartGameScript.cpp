#include "StartGameScript.h"

#include <crepe/api/Animator.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Sprite.h>

using namespace crepe;
using namespace std;

void StartGameScript::fixed_update(crepe::duration_t dt) {
	Transform & player_transform = this->get_components_by_name<Transform>("player").front();

	// Create hole in wall and activate panic lamp
	if (player_transform.position.x > 75 && !this->created_hole) {
		Sprite & lamp_sprite = this->get_components_by_name<Sprite>("start_end").back();
		lamp_sprite.active = true;
		Sprite & hole_sprite = this->get_components_by_name<Sprite>("start_hole").front();
		hole_sprite.active = true;

		RefVector<Rigidbody> frags_rg
			= this->get_components_by_tag<Rigidbody>("wall_fragment");
		RefVector<Sprite> frags_sprite = this->get_components_by_tag<Sprite>("wall_fragment");
		for (Rigidbody & frag_rg : frags_rg) {
			frag_rg.active = true;
		}
		for (Sprite & frag_sprite : frags_sprite) {
			frag_sprite.active = true;
		}

		RefVector<ParticleEmitter> smoke_emitters
			= this->get_components_by_name<ParticleEmitter>("smoke_particles");
		for (ParticleEmitter & emitter : smoke_emitters) {
			emitter.active = true;
		}

		this->created_hole = true;
	}

	// Take jetpack from jetpack stand
	if (player_transform.position.x > 275 && !this->took_jetpack) {
		Animator & jetpack_stand_anim
			= this->get_components_by_name<Animator>("start_begin").back();
		jetpack_stand_anim.next_anim();
		Sprite & jetpack_sprite = this->get_components_by_name<Sprite>("player").back();
		jetpack_sprite.active = true;

		this->took_jetpack = true;
	}

	// Start camera movement, enable player jumping and disable this script
	if (player_transform.position.x > 500) {
		Rigidbody & rb = this->get_components_by_name<Rigidbody>("camera").front();
		rb.data.linear_velocity = vec2(100, 0);
		BehaviorScript & player_script
			= this->get_components_by_name<BehaviorScript>("player").front();
		player_script.active = true;
		BehaviorScript & this_script
			= this->get_components_by_name<BehaviorScript>("start_game_script").front();
		this_script.active = false;
	}
}
