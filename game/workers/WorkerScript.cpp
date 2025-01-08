#include "WorkerScript.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>
#include <cstdlib>

using namespace crepe;
using namespace std;

void WorkerScript::fixed_update(duration_t dt) {
	RefVector<Rigidbody> rb_workers = this->get_components_by_tag<Rigidbody>("worker");
	RefVector<Transform> trans_workers = this->get_components_by_tag<Transform>("worker");

	Rigidbody & rb_cam = this->get_components_by_name<Rigidbody>("camera").back();
	Transform & trans_cam = this->get_components_by_name<Transform>("camera").back();

	int counter = 0;
	for (Rigidbody & rb_worker : rb_workers) {
		Transform & trans_worker = trans_workers.at(counter);

		float result_x = rb_cam.data.linear_velocity.x - rb_worker.data.linear_velocity.x;

		if (result_x > 0) {
			float left_cam_pos_x = trans_cam.position.x - VIEWPORT_X / 2;
			if (trans_worker.position.x < left_cam_pos_x - 1000) {
				trans_worker.position.x = left_cam_pos_x + VIEWPORT_X + 1000;

				do {
					float min_value = -2500 * dt.count();
					float max_value = 2500 * dt.count();
					rb_worker.data.linear_velocity.x
						= min_value
						  + static_cast<float>(rand())
								/ (static_cast<float>(RAND_MAX / (max_value - min_value)));
				} while (rb_worker.data.linear_velocity.x < 500 * dt.count()
						 && rb_worker.data.linear_velocity.x > -500 * dt.count());

				RefVector<Sprite> sprite_worker
					= this->get_components_by_id<Sprite>(trans_worker.game_object_id);
				RefVector<Animator> animator_worker
					= this->get_components_by_id<Animator>(trans_worker.game_object_id);

				if (rb_worker.data.linear_velocity.x < 0) {
					sprite_worker.front().get().data.flip.flip_x = true;
					sprite_worker.back().get().data.flip.flip_x = true;

					animator_worker.front().get().data.fps
						= -rb_worker.data.linear_velocity.x / 5;
					animator_worker.back().get().data.fps
						= -rb_worker.data.linear_velocity.x / 5;
					animator_worker.front().get().set_anim(0);
					animator_worker.back().get().set_anim(0);
				} else {
					sprite_worker.front().get().data.flip.flip_x = false;
					sprite_worker.back().get().data.flip.flip_x = false;

					animator_worker.front().get().data.fps
						= rb_worker.data.linear_velocity.x / 5;
					animator_worker.back().get().data.fps
						= rb_worker.data.linear_velocity.x / 5;
					animator_worker.front().get().set_anim(0);
					animator_worker.back().get().set_anim(0);
				}
			}
		} else {
			float right_cam_pos_x = trans_cam.position.x + VIEWPORT_X / 2;
			if (trans_worker.position.x > right_cam_pos_x + 1000) {
				do {
					float min_value = -2500 * dt.count();
					float max_value = 2500 * dt.count();
					rb_worker.data.linear_velocity.x
						= min_value
						  + static_cast<float>(rand())
								/ (static_cast<float>(RAND_MAX / (max_value - min_value)));
				} while (rb_worker.data.linear_velocity.x < 500 * dt.count()
						 && rb_worker.data.linear_velocity.x > -500 * dt.count());

				RefVector<Sprite> sprite_worker
					= this->get_components_by_id<Sprite>(trans_worker.game_object_id);
				RefVector<Animator> animator_worker
					= this->get_components_by_id<Animator>(trans_worker.game_object_id);

				if (rb_worker.data.linear_velocity.x < 0) {
					sprite_worker.front().get().data.flip.flip_x = true;
					sprite_worker.back().get().data.flip.flip_x = true;

					animator_worker.front().get().data.fps
						= -rb_worker.data.linear_velocity.x / 5;
					animator_worker.back().get().data.fps
						= -rb_worker.data.linear_velocity.x / 5;

					animator_worker.front().get().set_anim(0);
					animator_worker.back().get().set_anim(0);
				} else {
					sprite_worker.front().get().data.flip.flip_x = false;
					sprite_worker.back().get().data.flip.flip_x = false;

					animator_worker.front().get().data.fps
						= rb_worker.data.linear_velocity.x / 5;
					animator_worker.back().get().data.fps
						= rb_worker.data.linear_velocity.x / 5;

					animator_worker.front().get().set_anim(0);
					animator_worker.back().get().set_anim(0);
				}
			}
		}

		counter++;
	}
}
