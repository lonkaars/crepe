#include <cstdint>

#include "../api/Animator.h"
#include "../facade/SDLContext.h"
#include "../manager/ComponentManager.h"

#include "AnimatorSystem.h"

using namespace crepe;

void AnimatorSystem::update() {
	ComponentManager & mgr = this->component_manager;

	RefVector<Animator> animations = mgr.get_components_by_type<Animator>();

	uint64_t tick = SDLContext::get_instance().get_ticks();
	for (Animator & a : animations) {
		if (a.active) {
			a.curr_row = (tick / 100) % a.row;
			a.animator_rect.x = (a.curr_row * a.animator_rect.w) + a.curr_col;
			a.spritesheet.sprite_rect = a.animator_rect;
		}
	}
}
