#include "../api/BehaviorScript.h"
#include "../api/Script.h"
#include "../manager/ComponentManager.h"
#include "../util/dbg.h"

#include "ScriptSystem.h"

using namespace std;
using namespace crepe;

void ScriptSystem::fixed_update() {
	dbg_trace();

	ComponentManager & mgr = this->mediator.component_manager;
	LoopTimerManager & timer = this->mediator.loop_timer;
	RefVector<BehaviorScript> behavior_scripts = mgr.get_components_by_type<BehaviorScript>();

	for (BehaviorScript & behavior_script : behavior_scripts) {
		if (!behavior_script.active) continue;

		Script * script = behavior_script.script.get();
		if (script == nullptr) continue;

		if (!script->initialized) {
			script->init();
			script->initialized = true;
		}

		duration_t delta_time = timer.get_scaled_fixed_delta_time();
		script->update(delta_time);
	}
}
