

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

		double frame_duration = 1.0f / a.fps;

		int cycle_end = (a.cycle_end == -1) ? a.row : cycle_end;
		int total_frames = cycle_end - a.cycle_start;


		int curr_frame = static_cast<int>(elapsed_time / frame_duration) % total_frames;

		a.curr_row = a.cycle_start + curr_frame;
		a.spritesheet.mask.x = std::clamp((a.curr_row * a.spritesheet.mask.w - a.offset_x), 0, a.spritesheet.mask.w);
		a.spritesheet.mask.y = (a.curr_col * a.spritesheet.mask.h);

		if (!a.looping && curr_frame == total_frames) {
			a.active = false;
		}
	}
}
