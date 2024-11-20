#include "Script.h"

using namespace crepe;

Script::~Script() {
	EventManager & evmgr = *this->event_manager_ref;
	for (auto id : this->listeners) {
		evmgr.unsubscribe(id);
	}
}

