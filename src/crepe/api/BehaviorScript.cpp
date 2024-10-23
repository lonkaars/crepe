#include "../util/log.h"

#include "BehaviorScript.h"
#include "Script.h"

using namespace crepe::api;

BehaviorScript::BehaviorScript() : Component(gameObjectId) { dbg_trace(); }
