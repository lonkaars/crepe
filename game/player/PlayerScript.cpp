#include <iostream>
#include "PlayerScript.h"

#include "../Config.h"
#include "../enemy/BattleScript.h"
#include <crepe/api/Animator.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void PlayerScript::init() {
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool {
		return this->on_collision(ev);
	});
}
bool PlayerScript::on_collision(const CollisionEvent & ev) {
	BehaviorScript & play_scr = this->get_components_by_name<BehaviorScript>("player").front();
	BehaviorScript & end_scr = this->get_components_by_name<BehaviorScript>("player").back();
	RefVector<Animator> animators = this->get_components_by_name<Animator>("player");
	RefVector<ParticleEmitter> emitters
		= this->get_components_by_name<ParticleEmitter>("player");

	if (ev.info.other.metadata.tag == "zapper") {
		for (Animator & anim : animators) {
			anim.active = true;
			anim.set_anim(4);
			anim.data.looping = true;
			prev_anim = 0;
		}
		for (ParticleEmitter & emitter : emitters) {
			emitter.data.emission_rate = 0;
		}
		play_scr.active = false;
		end_scr.active = true;
		return true;
	} else if (ev.info.other.metadata.tag == "laser") {
		for (Animator & anim : animators) {
			anim.active = true;
			anim.set_anim(4);
			anim.data.looping = true;
			prev_anim = 0;
		}
		for (ParticleEmitter & emitter : emitters) {
			emitter.data.emission_rate = 0;
		}
		play_scr.active = false;
		end_scr.active = true;
		return true;
	} else if (ev.info.other.metadata.tag == "missile") {
		for (Animator & anim : animators) {
			anim.active = true;
			anim.set_anim(5);
			anim.data.looping = true;
			prev_anim = 0;
		}
		for (ParticleEmitter & emitter : emitters) {
			emitter.data.emission_rate = 0;
		}
		play_scr.active = false;
		end_scr.active = true;
		return true;
	}

	return false;
}

void PlayerScript::fixed_update(crepe::duration_t dt) {
	RefVector<Animator> animators = this->get_components_by_name<Animator>("player");
	RefVector<ParticleEmitter> emitters
		= this->get_components_by_name<ParticleEmitter>("player");
	Transform & transform = this->get_components_by_name<Transform>("player").front();

	for (ParticleEmitter & emitter : emitters) {
		emitter.data.boundary.offset = vec2(0, -transform.position.y);
	}
	
	Rigidbody & rb = this->get_components_by_name<Rigidbody>("player").front();
	if (this->get_key_state(Keycode::P)) {
		this->trigger_event<BattleStartEvent>(BattleStartEvent{
			.num_enemies = 5,
		});
	}
	if(this->get_key_state(Keycode::ENTER)){
		this->shoot(transform.position,0);
	}
	if (this->get_key_state(Keycode::SPACE)) {
		rb.add_force_linear(vec2(0, -PLAYER_GRAVITY_SCALE / 2.5) * dt.count() / 0.02);
		if (prev_anim != 1) {
			for (Animator & anim : animators) {
				anim.active = true;
				anim.set_anim(1);
				anim.data.looping = true;
				prev_anim = 1;
			}
			for (ParticleEmitter & emitter : emitters) {
				emitter.data.emission_rate = 30;
			}
		}
	} else if (transform.position.y == 195) {
		if (prev_anim != 0) {
			for (Animator & anim : animators) {
				anim.active = true;
				anim.set_anim(0);
				anim.data.looping = true;
				prev_anim = 0;
			}
			for (ParticleEmitter & emitter : emitters) {
				emitter.data.emission_rate = 0;
			}
		}
	} else {
		if (prev_anim != 2) {
			for (Animator & anim : animators) {
				anim.set_anim(2);
				anim.data.looping = false;
				prev_anim = 2;
			}
			for (ParticleEmitter & emitter : emitters) {
				emitter.data.emission_rate = 0;
			}
		}
	}
}

void PlayerScript::shoot(const vec2& location,float angle){
	cout << "player shot" << endl;
	RefVector<Transform> bullet_transforms = this->get_components_by_tag<Transform>("PlayerBullet");

	for(Transform& bullet_pos : bullet_transforms){
		//cout << "bullet pos  x: " << bullet_pos.position.x << " y: " << bullet_pos.position.y << endl;
		if(bullet_pos.position.x == 0 && bullet_pos.position.y == -850){
			
			cout << "bullet found\n";
			bullet_pos.position = location;
			bullet_pos.position.x += 20;
			cout << "bullet pos  x: " << bullet_pos.position.x << " y: " << bullet_pos.position.y << endl;
			Rigidbody& bullet_body = this->get_components_by_id<Rigidbody>(bullet_pos.game_object_id).front();
			BoxCollider bullet_collider = this->get_components_by_id<BoxCollider>(bullet_pos.game_object_id).front();
			//bullet_collider.active = true;
			bullet_body.active = true;
			return;
		}
	}
	cout << "bullet not found\n";
}
