#include "CollisionScript.h"

#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void CollisionScript::init() {
	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool {
		return this->on_collision(ev);
	});
}

bool CollisionScript::on_collision(const CollisionEvent & ev) {
	RefVector<Animator> animators = this->get_components<Animator>();
	RefVector<Sprite> sprites = this->get_components<Sprite>();
	Rigidbody & rb = this->get_component<Rigidbody>();
	Transform & tr = this->get_component<Transform>();
	BehaviorScript & bs_panic = this->get_components<BehaviorScript>().front();

	if (ev.info.other.metadata.tag == "zapper") {
		for (Animator & anim : animators) {
			anim.active = false;
			anim.set_anim(3);
		}
		for (Sprite & sprite : sprites) {
			sprite.data.position_offset.x = 15;
		}
		rb.data.linear_velocity_coefficient = {0.5, 0.5};
		tr.rotation = 90;
		bs_panic.active = false;

		return false;
	} else if (ev.info.other.metadata.tag == "laser") {
		for (Animator & anim : animators) {
			anim.active = false;
			anim.set_anim(3);
		}
		for (Sprite & sprite : sprites) {
			sprite.data.position_offset.x = 15;
		}
		rb.data.linear_velocity_coefficient = {0.5, 0.5};
		tr.rotation = 90;
		bs_panic.active = false;

		return false;
	} else if (ev.info.other.metadata.tag == "missile" || ev.info.other.metadata.tag == "enemy_bullet") {
		for (Animator & anim : animators) {
			anim.active = false;
			anim.set_anim(3);
		}
		for (Sprite & sprite : sprites) {
			sprite.data.position_offset.x = 15;
		}
		rb.data.linear_velocity_coefficient = {0.5, 0.5};
		tr.rotation = 90;
		bs_panic.active = false;

		return false;
	}

	return false;
}
