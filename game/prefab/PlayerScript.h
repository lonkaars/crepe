#pragma once

#include <crepe/api/Script.h>

#include "PlayerObject.h"

class PlayerScript : public crepe::Script {
public:
	PlayerScript(PlayerObject * player);

	PlayerScript(const PlayerScript &) = delete;
	PlayerScript(PlayerScript &&) = delete;
	PlayerScript & operator=(const PlayerScript &) = delete;
	PlayerScript & operator=(PlayerScript &&) = delete;

protected:
	void fixed_update(crepe::duration_t dt);
	void init();

protected:
	PlayerObject * player = nullptr;
};

