#include "EventSystem.h"
#include "../manager/EventManager.h"

using namespace crepe;

void EventSystem::fixed_update() {
	EventManager & ev = this->mediator.event_manager;
	ev.dispatch_events();
}
