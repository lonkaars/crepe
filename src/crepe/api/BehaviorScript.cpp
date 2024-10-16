#include "../util/log.h"

#include "Script.h"
#include "BehaviorScript.h"

using namespace crepe::api;

BehaviorScript::BehaviorScript() {
	dbg_trace();
}

BehaviorScript::~BehaviorScript() {
	if (this->script != nullptr) {
		delete this->script;
		this->script = nullptr;
	}
}

