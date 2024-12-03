

#include "api/Animator.h"

#include "AnimatorSystem.h"
#include "ComponentManager.h"

using namespace crepe;

void AnimatorSystem::update() {
	ComponentManager & mgr = this->component_manager;

	RefVector<Animator> animations = mgr.get_components_by_type<Animator>();

	double elapsed_time = this->timer.get_current_time();

	for (Animator & a : animations) {
		if (!a.active) continue;

		Animator::Data & ctx = a.data;
		double frame_duration = 1.0f / ctx.fps;

		int last_frame = ctx.curr_row;

		int cycle_end = (ctx.cycle_end == -1) ? ctx.row : ctx.cycle_end;
		int total_frames = cycle_end - ctx.cycle_start;

		int curr_frame = static_cast<int>(elapsed_time / frame_duration) % total_frames;

		ctx.curr_row = ctx.cycle_start + curr_frame;
		ctx.spritesheet.mask.x = ctx.curr_row * ctx.spritesheet.mask.w;
		ctx.spritesheet.mask.y = (ctx.curr_col * ctx.spritesheet.mask.h);

		if (!ctx.looping && curr_frame == ctx.cycle_start && last_frame == total_frames - 1) {
			a.active = false;
		}
	}
}
