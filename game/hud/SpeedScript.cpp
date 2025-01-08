#include "SpeedScript.h"

#include <crepe/api/Event.h>
#include <crepe/api/KeyCodes.h>
#include <crepe/manager/LoopTimerManager.h>

using namespace crepe;
using namespace std;

void SpeedScript::init() {
	this->subscribe<KeyPressEvent>([this](const KeyPressEvent & ev) -> bool {
		if (ev.key != Keycode::HOME) return false;
		LoopTimerManager & lp = this->get_loop_timer();
		this->toggle = !this->toggle;
		if (this->toggle) {
			this->timescale = lp.get_time_scale();
			lp.set_time_scale(0);
		} else {
			lp.set_time_scale(this->timescale);
		}

		return true;
	});
}

void SpeedScript::fixed_update(crepe::duration_t dt) {
	LoopTimerManager & lp = this->get_loop_timer();
	if (this->get_key_state(Keycode::PAGE_UP)) {
		if(lp.get_time_scale() >= 2) return;
		lp.set_time_scale(lp.get_time_scale() + 0.1);
	}
	if (this->get_key_state(Keycode::PAGE_DOWN)) {
		if(lp.get_time_scale() <= 0.5) return;
		lp.set_time_scale(lp.get_time_scale() - 0.1);
	}
}
