#include "BehaviorScript.h"
#include "Component.h"

using namespace crepe;

BehaviorScript::BehaviorScript(game_object_id_t id, ComponentManager & mgr) : Component(id), component_manager(mgr) {}

