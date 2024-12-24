#pragma once

#include <crepe/api/Script.h>

class EndGameScript : public crepe::Script {
public:
	void fixed_update(crepe::duration_t dt);
};
