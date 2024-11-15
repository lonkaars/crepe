#include <forward_list>
#include <functional>
#include <vector>

#include "../ComponentManager.h"
#include "../api/BehaviorScript.h"
#include "../api/Script.h"
#include "../util/log.h"

#include "ScriptSystem.h"

using namespace std;
using namespace crepe;

void ScriptSystem::update() {
	using namespace std;
	dbg_trace();

	forward_list<Script *> scripts = this->get_scripts();
	for (Script * script : scripts) 
	{
		script->init();
		script->update();
	};
}

forward_list<Script *> ScriptSystem::get_scripts() {
	forward_list<Script *> scripts = {};
	ComponentManager & mgr = ComponentManager::get_instance();
	vector<reference_wrapper<BehaviorScript>> behavior_scripts
		= mgr.get_components_by_type<BehaviorScript>();

	for (auto behavior_script_ref : behavior_scripts) {
		BehaviorScript & behavior_script = behavior_script_ref.get();
		if (!behavior_script.active) continue;
		Script * script = behavior_script.script.get();
		if (script == nullptr) continue;
		scripts.push_front(script);
	}

	return scripts;
}
