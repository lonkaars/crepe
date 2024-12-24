#include "EndGameScript.h"

#include <crepe/api/Animator.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void EndGameScript::init() {
	BoxCollider jetpack_coll = this->get_components_by_name<BoxCollider>("player").back();
	CircleCollider head_coll = this->get_components_by_name<CircleCollider>("player").back();
	jetpack_coll.active = false;
	head_coll.active = false;
}

void EndGameScript::fixed_update(crepe::duration_t dt) {
	Transform & transform_player = this->get_components_by_name<Transform>("player").front();
	RefVector<Animator> anim_player = this->get_components_by_name<Animator>("player");
	Rigidbody & rb_player = this->get_components_by_name<Rigidbody>("player").front();
	Rigidbody & rb_camera = this->get_components_by_name<Rigidbody>("camera").front();

	if (transform_player.position.y >= 194) {
		if (jump == 0 || jump == 1) {
			int random_number = rand() % 4;
			for (Animator & anim : anim_player) {
				anim.active = false;
				anim.set_anim(6);
				for (int i = 0; i < random_number; i++) {
					anim.next_anim();
				}
			}
		} else if (jump == 2) {
			for (Animator & anim : anim_player) {
				anim.active = false;
				anim.set_anim(7);
			}
			rb_player.data.angular_velocity = 0;
			transform_player.rotation = 90;
		}
		if (jump == 0) {
			rb_player.data.linear_velocity = vec2(100, -150);
			rb_player.data.angular_velocity = 320;
			rb_player.data.angular_velocity_coefficient = 0.8;
			jump++;
		} else if (jump == 1) {
			rb_player.data.linear_velocity = vec2(100, -125);
			rb_player.data.angular_velocity = 300;
			rb_player.data.angular_velocity_coefficient = 0.8;
			jump++;
		} else if (jump == 2) {
			rb_player.data.linear_velocity = vec2(100, 0);
			rb_player.data.linear_velocity_coefficient = vec2(0.5, 0.5);
			rb_camera.data.linear_velocity_coefficient = vec2(0.5, 0.5);
			jump++;
		}
	}
}
