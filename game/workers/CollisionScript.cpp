#include "CollisionScript.h"

#include <crepe/api/Animator.h>

using namespace crepe;
using namespace std;

void CollisionScript::init() {
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool {
		return this->on_collision(ev);
	});
}

bool CollisionScript::on_collision(const CollisionEvent & ev) {
	RefVector<Animator> animators = this->get_components<Animator>();

	if (ev.info.other.metadata.tag == "zapper") {
		for (Animator & anim : animators) {
			anim.active = true;
			anim.set_anim(4);
			anim.data.looping = true;
		}

		return true;
	} else if (ev.info.other.metadata.tag == "laser") {
		for (Animator & anim : animators) {
			anim.active = true;
			anim.set_anim(4);
			anim.data.looping = true;
		}

		return true;
	} else if (ev.info.other.metadata.tag == "missile") {
		for (Animator & anim : animators) {
			anim.active = true;
			anim.set_anim(5);
			anim.data.looping = true;
		}

		return true;
	}

	return false;
}
