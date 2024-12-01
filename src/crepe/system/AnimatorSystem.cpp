#include <cstdint>

#include "api/Animator.h"
#include "facade/SDLContext.h"

#include "AnimatorSystem.h"
#include "ComponentManager.h"

using namespace crepe;

void AnimatorSystem::update() {
	ComponentManager & mgr = this->component_manager;

	RefVector<Animator> animations = mgr.get_components_by_type<Animator>();

	uint64_t tick = SDLContext::get_instance().get_ticks();
	for (Animator & a : animations) {
		if (!a.active) continue;
		// (10 frames per second)
		a.curr_row = (tick / 100) % a.row;
		a.spritesheet.mask.x = (a.curr_row * a.spritesheet.mask.w) + a.curr_col;
		a.spritesheet.mask = a.spritesheet.mask;
	}
}
