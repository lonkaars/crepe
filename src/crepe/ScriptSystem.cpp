#include <forward_list>
#include <functional>
#include <vector>

#include "ScriptSystem.h"
#include "ComponentManager.h"
#include "api/BehaviorScript.h"
#include "api/Script.h"
#include "util/log.h"

using namespace std;
using namespace crepe;
using namespace crepe::api;

ScriptSystem::ScriptSystem() {
	dbg_trace();
}
ScriptSystem::~ScriptSystem() {
	dbg_trace();
}

ScriptSystem & ScriptSystem::get_instance() {
	static ScriptSystem instance;
	return instance;
}

void ScriptSystem::update() {
	using namespace std;
	dbg_trace();

	forward_list<Script *> scripts = this->get_scripts();
	for (Script * script : scripts)
		script->update();
}

forward_list<Script *> ScriptSystem::get_scripts() {
	forward_list<Script *> scripts = {};
	ComponentManager & mgr = ComponentManager::get_instance();
	vector<reference_wrapper<BehaviorScript>> behavior_scripts = mgr.get_components_by_type<BehaviorScript>();

	for (auto behavior_script_ref : behavior_scripts) {
		BehaviorScript & behavior_script = behavior_script_ref.get();
		Script * script = behavior_script.script;
		if (script == nullptr) continue;
		scripts.push_front(script);
	}

	return scripts;
}

