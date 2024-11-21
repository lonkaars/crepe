#include <functional>

#include "../ComponentManager.h"
#include "../api/BehaviorScript.h"
#include "../api/Script.h"

#include "ScriptSystem.h"

using namespace std;
using namespace crepe;

void ScriptSystem::update() {
	dbg_trace();

	RefVector<Script> scripts = this->get_scripts();

	for (auto & script_ref : scripts) {
		Script & script = script_ref.get();
		if (!script.initialized) {
			script.init();
			script.initialized = true;
		}
		script.update();
	}
}

RefVector<Script> ScriptSystem::get_scripts() const {
	RefVector<Script> scripts = {};
	ComponentManager & mgr = this->component_manager;
	RefVector<BehaviorScript> behavior_scripts = mgr.get_components_by_type<BehaviorScript>();

	for (auto behavior_script_ref : behavior_scripts) {
		BehaviorScript & behavior_script = behavior_script_ref.get();
		if (!behavior_script.active) continue;
		Script * script = behavior_script.script.get();
		if (script == nullptr) continue;
		scripts.push_back(*script);
	}

	return scripts;
}
