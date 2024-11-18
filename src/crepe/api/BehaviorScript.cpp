#include "BehaviorScript.h"
#include "Component.h"
#include "GameObject.h"

using namespace crepe;

BehaviorScript::BehaviorScript(game_object_id_t id, ComponentManager & mgr)
	: Component(id),
	  component_manager(mgr) {}

template <>
BehaviorScript & GameObject::add_component<BehaviorScript>() {
	ComponentManager & mgr = this->component_manager;
	return mgr.add_component<BehaviorScript>(this->id, mgr);
}
