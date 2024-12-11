

#include "../api/Animator.h"
#include "../manager/ComponentManager.h"
#include "api/LoopTimer.h"

#include "AnimatorSystem.h"

using namespace crepe;

void AnimatorSystem::update() {
	ComponentManager & mgr = this->mediator.component_manager;
	LoopTimer & timer = this->mediator.timer;
	RefVector<Animator> animations = mgr.get_components_by_type<Animator>();

	double elapsed_time = timer.get_current_time();

	for (Animator & a : animations) {
		if (!a.active) continue;

		Animator::Data & ctx = a.data;
		float frame_duration = 1.0f / ctx.fps;

		int last_frame = ctx.row;

		int cycle_end = (ctx.cycle_end == -1) ? a.grid_size.x : ctx.cycle_end;
		int total_frames = cycle_end - ctx.cycle_start;

		int curr_frame = static_cast<int>(elapsed_time / frame_duration) % total_frames;

		ctx.row = ctx.cycle_start + curr_frame;
		a.spritesheet.mask.x = ctx.row * a.spritesheet.mask.w;
		a.spritesheet.mask.y = (ctx.col * a.spritesheet.mask.h);

		if (!ctx.looping && curr_frame == ctx.cycle_start && last_frame == total_frames - 1) {
			a.active = false;
		}
	}
}
