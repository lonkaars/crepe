#include "CollisionScript.h"

#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/ParticleEmitter.h>


using namespace crepe;
using namespace std;

void CollisionScript::init() {
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool {
		return this->on_collision(ev);
	});
}

bool CollisionScript::on_collision(const CollisionEvent & ev) {
	RefVector<Animator> animators = this->get_components_by_name<Animator>("player");
	RefVector<ParticleEmitter> emitters
		= this->get_components_by_name<ParticleEmitter>("player");

	if (ev.info.other.metadata.tag == "zapper") {
		for (Animator & anim : animators) {
			anim.active = true;
			anim.set_anim(4);
			anim.data.looping = true;
		}
		for (ParticleEmitter & emitter : emitters) {
			emitter.data.emission_rate = 0;
		}

		return true;
	} else if (ev.info.other.metadata.tag == "laser") {
		for (Animator & anim : animators) {
			anim.active = true;
			anim.set_anim(4);
			anim.data.looping = true;
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
