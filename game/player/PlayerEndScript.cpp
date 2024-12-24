#include "PlayerEndScript.h"

#include <crepe/api/Animator.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void PlayerEndScript::init() {
	Rigidbody & rb_player = this->get_components_by_name<Rigidbody>("player").front();
	rb_player.data.elasticity_coefficient = 0.7;

	subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool {
		return this->on_collision(ev);
	});
}

bool PlayerEndScript::on_collision(const crepe::CollisionEvent & ev) {
	if (ev.info.other.metadata.name == "floor") {
		Transform & transform_player
			= this->get_components_by_name<Transform>("player").front();
		RefVector<Animator> anim_player = this->get_components_by_name<Animator>("player");
		Rigidbody & rb_player = this->get_components_by_name<Rigidbody>("player").front();
		Rigidbody & rb_camera = this->get_components_by_name<Rigidbody>("camera").front();

		if (jump == 0 || jump == 1) {
			int random_number = rand() % 4;
			for (Animator & anim : anim_player) {
				anim.active = false;
				anim.set_anim(6);
				for (int i = 0; i < random_number; i++) {
					anim.next_anim();
				}
			}
		}

		if (jump == 0) {
			rb_player.data.angular_velocity = 320;
			rb_player.data.angular_velocity_coefficient = 0.7;
			jump++;
		} else if (jump == 1 && transform_player.rotation > 65
				   && transform_player.rotation < 115) {
			rb_player.data.angular_velocity = 0;
			rb_player.data.elasticity_coefficient = 0;
			rb_player.data.linear_velocity = vec2(100, 0);
			rb_player.data.linear_velocity_coefficient = vec2(0.5, 0.5);
			rb_camera.data.linear_velocity_coefficient = vec2(0.5, 0.5);
			for (Animator & anim : anim_player) {
				anim.active = false;
				anim.set_anim(7);
			}
			jump++;
		}

		return true;
	}

	return false;
}
