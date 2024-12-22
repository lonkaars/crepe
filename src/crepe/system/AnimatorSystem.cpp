#include "../api/Animator.h"
#include "../manager/ComponentManager.h"
#include "../manager/LoopTimerManager.h"
#include <chrono>

#include "AnimatorSystem.h"

using namespace crepe;
using namespace std::chrono;

void AnimatorSystem::frame_update() {
	ComponentManager & mgr = this->mediator.component_manager;
	LoopTimerManager & timer = this->mediator.loop_timer;
	RefVector<Animator> animations = mgr.get_components_by_type<Animator>();

	duration_t elapsed = timer.get_delta_time();

	for (Animator & animator : animations) {
		if (!animator.active) continue;

		Animator::Data & data = animator.data;
		if (animator.data.fps == 0) continue;

		if (animator.data.cycle_end == -1)
			animator.data.cycle_end = animator.grid_size.x * animator.grid_size.y;

		animator.elapsed += elapsed;
		duration_t frame_duration = 1000ms / animator.data.fps;

		if (animator.elapsed > frame_duration) {
			animator.elapsed = 0ms;
			animator.data.frame++;

			if (animator.data.looping && animator.data.frame >= animator.data.cycle_end)
				animator.data.frame = animator.data.cycle_start;
		}

		Sprite::Mask & mask = animator.spritesheet.mask;
		mask.x = animator.data.frame % animator.grid_size.x * mask.w;
		mask.y = animator.data.frame / animator.grid_size.x * mask.h;
	}
}
