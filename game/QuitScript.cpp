

#include "QuitScript.h"

#include <crepe/api/Event.h>
#include <crepe/api/KeyCodes.h>

using namespace crepe;

bool QuitScript::on_event(const KeyPressEvent & ev) {
	if (Keycode::ESCAPE == ev.key) {
		trigger_event<ShutDownEvent>(ShutDownEvent {});
	}
	return false;
}

void QuitScript::init() {
	subscribe<KeyPressEvent>([this](const KeyPressEvent & ev) -> bool {
		return this->on_event(ev);
	});
}
