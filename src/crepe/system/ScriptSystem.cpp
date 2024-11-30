#include "../api/BehaviorScript.h"
#include "../api/Script.h"
#include "../manager/ComponentManager.h"

#include "ScriptSystem.h"

using namespace std;
using namespace crepe;

void ScriptSystem::update() {
	dbg_trace();

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
		script->update();
	}
}
