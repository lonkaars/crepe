#pragma once

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

class PlayerAudioScript : public crepe::Script {
public:
	void fixed_update(crepe::duration_t dt);

private:
	int last_row = -1;
	int current_footstep = 0;
};
