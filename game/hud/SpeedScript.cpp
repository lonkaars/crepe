#include "SpeedScript.h"
#include "api/KeyCodes.h"
#include "manager/LoopTimerManager.h"

using namespace crepe;
using namespace std;

void SpeedScript::fixed_update(crepe::duration_t dt){
	LoopTimerManager & lp =  this->get_loop_timer();
	if(this->get_key_state(Keycode::HOME)){
		if(toggle)
		{
			this->timescale = lp.get_time_scale(); 
			lp.set_time_scale(0);
			toggle = false;
		}
		else {
			lp.set_time_scale(this->timescale);
			toggle = true;
		}
	}
	if(this->get_key_state(Keycode::PAGE_UP)){
		lp.set_time_scale(lp.get_time_scale()+0.1);
	}
	if(this->get_key_state(Keycode::PAGE_DOWN)){
		lp.set_time_scale(lp.get_time_scale()-0.1);
	}
}
