#include "../manager/EventManager.h"
#include "EventSystem.h"

using namespace crepe;

void EventSystem::fixed_update() {
	EventManager & ev = this->mediator.event_manager;
	ev.dispatch_events();
}

