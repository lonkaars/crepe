#include "Script.h"

using namespace crepe;

Script::~Script() {
	EventManager & evmgr = this->event_manager;
	for (auto id : this->listeners) {
		evmgr.unsubscribe(id);
	}
}

template <>
void Script::subscribe(const EventHandler<CollisionEvent> & callback) {
	this->subscribe_internal(callback, this->game_object_id);
}
