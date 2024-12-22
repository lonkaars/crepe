#pragma once

#include <crepe/api/Script.h>

#include "PlayerObject.h"

class PlayerScript : public crepe::Script {
public:
	PlayerScript(const PlayerObject & player);

protected:
	void fixed_update(crepe::duration_t dt);

protected:
	PlayerObject player;
};
