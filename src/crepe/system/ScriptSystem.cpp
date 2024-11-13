#include <forward_list>
#include <functional>
#include <vector>

#include "../ComponentManager.h"
#include "../api/BehaviorScript.h"
#include "../api/Script.h"

#include "ScriptSystem.h"

using namespace std;
using namespace crepe;

void ScriptSystem::update() {
	dbg_trace();

	forward_list<reference_wrapper<Script>> scripts = this->get_scripts();

	for (auto & script_ref : scripts) {
		Script & script = script_ref.get();
		BehaviorScript & component = *script.parent_ref;
		if (!component.initialized) {
			script.init();
			component.initialized = true;
		}
		script.update();
	}
}

forward_list<reference_wrapper<Script>> ScriptSystem::get_scripts() const {
	forward_list<reference_wrapper<Script>> scripts = {};
	ComponentManager & mgr = this->component_manager;
	vector<reference_wrapper<BehaviorScript>> behavior_scripts
		= mgr.get_components_by_type<BehaviorScript>();

	for (auto behavior_script_ref : behavior_scripts) {
		BehaviorScript & behavior_script = behavior_script_ref.get();
		if (!behavior_script.active) continue;
		Script * script = behavior_script.script.get();
		if (script == nullptr) continue;
		scripts.push_front(*script);
	}

	return scripts;
}

