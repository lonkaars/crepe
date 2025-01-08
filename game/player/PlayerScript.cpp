#include "PlayerScript.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
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

		AudioSource & audio = this->get_components_by_name<AudioSource>("player").at(0);
		audio.play();

		return false;
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

		AudioSource & audio = this->get_components_by_name<AudioSource>("player").at(1);
		audio.play();

		return false;
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

		AudioSource & audio = this->get_components_by_name<AudioSource>("player").at(2);
		audio.play();

		return false;
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

		AudioSource & audio = this->get_components_by_name<AudioSource>("player").at(
			3 + current_jetpack_sound
		);
		audio.play();
		current_jetpack_sound++;
		if (current_jetpack_sound > 7) {
			current_jetpack_sound = 0;
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