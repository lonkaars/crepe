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

BehaviorScript::BehaviorScript(const BehaviorScript & other) : mediator(other.mediator), Component(other.game_object_id) {
	Log::logf("COPY CONSTRUCTOR!!!");
}

BehaviorScript::BehaviorScript(BehaviorScript && other) : mediator(other.mediator), Component(other.game_object_id) {
	Log::logf("MOVE CONSTRUCTOR!!!");
}

BehaviorScript & BehaviorScript::operator = (const BehaviorScript & other) {
	Log::logf("COPY OPERATOR!!!");
	return *this;
}

BehaviorScript & BehaviorScript::operator = (BehaviorScript && other) {
	Log::logf("MOVE OPERATOR!!!");
	return *this;
}
