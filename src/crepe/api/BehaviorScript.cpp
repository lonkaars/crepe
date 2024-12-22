#include "BehaviorScript.h"
#include "Component.h"
#include "GameObject.h"

using namespace crepe;

BehaviorScript::BehaviorScript(game_object_id_t id, Mediator & mediator)
	: Component(id),
	  mediator(mediator) {}

template <>
BehaviorScript & GameObject::add_component<BehaviorScript>() {
	ComponentManager & mgr = this->mediator.component_manager;
	return mgr.add_component<BehaviorScript>(this->id, this->mediator);
}
