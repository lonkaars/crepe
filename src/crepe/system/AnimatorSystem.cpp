#include <chrono>

#include "../api/Animator.h"
#include "../manager/ComponentManager.h"
#include "../manager/LoopTimerManager.h"

#include "AnimatorSystem.h"

using namespace crepe;
using namespace std::chrono;

void AnimatorSystem::frame_update() {
	ComponentManager & mgr = this->mediator.component_manager;
	LoopTimerManager & timer = this->mediator.loop_timer;
	RefVector<Animator> animations = mgr.get_components_by_type<Animator>();

	duration_t elapsed_time = timer.get_delta_time();

	for (Animator & a : animations) {
		if (!a.active) continue;
		if (a.data.fps == 0) continue;

		Animator::Data & ctx = a.data;

		a.elapsed_time += elapsed_time;
		duration_t frame_duration = 1000ms / ctx.fps;

		if (a.elapsed_time <= frame_duration) continue;

		a.elapsed_time = 0ms;
		a.frame++;

		int cycle_end = (ctx.cycle_end == -1) ? a.grid_size.x : ctx.cycle_end;
		int total_frames = cycle_end - ctx.cycle_start;
		int curr_cycle_frame = (a.frame - ctx.cycle_start) % total_frames;

		ctx.row = (ctx.cycle_start + curr_cycle_frame) % a.grid_size.x;
		ctx.col = curr_cycle_frame / a.grid_size.x;

		a.spritesheet.mask.x = ctx.row * a.spritesheet.mask.w;
		a.spritesheet.mask.y = ctx.col * a.spritesheet.mask.y;

		if (!ctx.looping && a.frame >= cycle_end) {
			a.active = false;
		}
	}
}
