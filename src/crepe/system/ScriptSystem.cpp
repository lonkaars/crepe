#include "../api/BehaviorScript.h"
#include "../api/Script.h"
#include "../manager/ComponentManager.h"

#include "ScriptSystem.h"

using namespace std;
using namespace crepe;

void ScriptSystem::fixed_update() {
	LoopTimerManager & timer = this->mediator.loop_timer;
	duration_t delta_time = timer.get_scaled_fixed_delta_time();
	this->update(&Script::fixed_update, delta_time);
}

void ScriptSystem::frame_update() {
	LoopTimerManager & timer = this->mediator.loop_timer;
	duration_t delta_time = timer.get_delta_time();
	this->update(&Script::frame_update, delta_time);
}

void ScriptSystem::update(void (Script::* update_function)(duration_t), const duration_t & delta_time) {
	ComponentManager & mgr = this->mediator.component_manager;
	RefVector<BehaviorScript> behavior_scripts = mgr.get_components_by_type<BehaviorScript>();

	for (BehaviorScript & behavior_script : behavior_scripts) {
		if (!behavior_script.active) continue;

		Script * script = behavior_script.script.get();
		if (script == nullptr) continue;

		if (!script->initialized) {
			script->init();
			script->initialized = true;
		}

		(*script.*update_function)(delta_time);
	}
}

