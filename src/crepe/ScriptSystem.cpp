#include "util/log.h"

#include "ScriptSystem.h"

using namespace crepe;

ScriptSystem::ScriptSystem() { dbg_trace(); }
ScriptSystem::~ScriptSystem() { dbg_trace(); }

ScriptSystem & ScriptSystem::get_instance() {
	static ScriptSystem instance;
	return instance;
}

void ScriptSystem::update() { dbg_trace(); }
