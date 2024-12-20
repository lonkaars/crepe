#pragma once

#include <crepe/api/Script.h>

class PlayerScript : public crepe::Script {
public:
	void fixed_update(crepe::duration_t dt);
};
