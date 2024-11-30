#include <string>

#include "../manager/SceneManager.h"

#include "Script.h"

using namespace crepe;
using namespace std;

Script::~Script() {
	Mediator & mediator = this->mediator;
	EventManager & mgr = mediator.event_manager;
	for (auto id : this->listeners) {
		mgr.unsubscribe(id);
	}
}

template <>
void Script::subscribe(const EventHandler<CollisionEvent> & callback) {
	this->subscribe_internal(callback, this->game_object_id);
}

void Script::set_next_scene(const string & name) {
	Mediator & mediator = this->mediator;
	SceneManager & mgr = mediator.scene_manager;
	mgr.set_next_scene(name);
}
