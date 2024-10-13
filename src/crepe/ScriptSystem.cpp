#include <vector>
#include "ComponentManager.h"
#include "api/BehaviorScript.h"
#include "util/fmt.h"
#include "util/log.h"

#include "ScriptSystem.h"

using namespace crepe;

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

	ComponentManager & mgr = ComponentManager::get_instance();
	vector<reference_wrapper<api::BehaviorScript>> scripts = mgr.get_components_by_type<api::BehaviorScript>();

	dbg_logf("script count: %lu", scripts.size());

}

