
#include <cstdint>
#include <functional>
#include <vector>

#include "facade/SDLContext.h"
#include "util/log.h"
#include "api/Animator.h"

#include "ComponentManager.h"
#include "AnimatorSystem.h"

using namespace crepe;

AnimatorSystem::AnimatorSystem() { dbg_trace(); }

AnimatorSystem::~AnimatorSystem() { dbg_trace(); }

AnimatorSystem & AnimatorSystem::get_instance() {
	static AnimatorSystem instance;
	return instance;
}

void AnimatorSystem::update() {
	ComponentManager& mgr = ComponentManager::get_instance();

	std::vector<std::reference_wrapper<Animator>> animations = mgr.get_components_by_type<Animator>();

	uint64_t tick = SDLContext::get_instance().get_ticks();
	for(Animator& a : animations){
		if (a.active) {
			a.curr_row = (tick / 100) % a.row;
			a.animator_rect.x = (a.curr_row * a.animator_rect.w) + a.curr_col;
			a.spritesheet.sprite_rect = a.animator_rect;
		}
	}
}

