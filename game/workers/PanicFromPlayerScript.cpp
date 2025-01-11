#include "PanicFromPlayerScript.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void PanicFromPlayerScript::fixed_update(duration_t dt) {
	Animator & anim_player = this->get_components_by_name<Animator>("player").front();

	if (anim_player.data.col == 1) {
		Transform & trans_player = this->get_components_by_name<Transform>("player").back();
		Transform & trans_worker = this->get_components<Transform>().back();

		float result_x = trans_player.position.x - trans_worker.position.x;

		if (result_x < 100 && result_x > -20) {
			RefVector<Animator> anim_worker = this->get_components<Animator>();
			RefVector<Sprite> sprite_worker = this->get_components<Sprite>();
			Rigidbody & rb_worker = this->get_components<Rigidbody>().back();

			if (anim_worker.front().get().data.col != 1) {
				anim_worker.front().get().set_anim(1);
				anim_worker.back().get().set_anim(1);

				anim_worker.front().get().data.fps = 10;
				anim_worker.back().get().data.fps = 10;
			}

			if (result_x < 0) {
				float min_value = 8000;
				float max_value = 10000;
				float value = min_value
							  + static_cast<float>(rand())
									/ (static_cast<float>(RAND_MAX / (max_value - min_value)));
				rb_worker.data.linear_velocity.x = value * dt.count();
				sprite_worker.front().get().data.flip.flip_x = false;
				sprite_worker.back().get().data.flip.flip_x = false;
			} else {
				float min_value = -4000;
				float max_value = -5000;
				float value = min_value
							  + static_cast<float>(rand())
									/ (static_cast<float>(RAND_MAX / (max_value - min_value)));
				rb_worker.data.linear_velocity.x = value * dt.count();
				sprite_worker.front().get().data.flip.flip_x = true;
				sprite_worker.back().get().data.flip.flip_x = true;
			}
		}
	}
};
