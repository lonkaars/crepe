#include "Script.h"

using namespace crepe;

Script::~Script() {
	EventManager & evmgr = *this->event_manager_ref;
	for (auto id : this->listeners) {
		evmgr.unsubscribe(id);
	}
}

template <>
void Script::subscribe(const EventHandler<CollisionEvent> & callback) {
	const game_object_id_t & game_object_id = *this->game_object_id_ref;
	this->subscribe_internal(callback, game_object_id);
}

