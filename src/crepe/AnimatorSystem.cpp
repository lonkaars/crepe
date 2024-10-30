

#include "AnimatorSystem.h"
#include "ComponentManager.h"
#include "SDLContext.h"
#include "util/log.h"

#include "api/Animator.h"

#include <cstdint>
#include <functional>
#include <vector>

using namespace crepe;
using namespace crepe::api;

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
		a.curr_row = (tick / 100) % a.ROW;
	}
}
