#pragma once

#include <crepe/api/Script.h>

class StartGameScript : public crepe::Script {
public:
	void fixed_update(crepe::duration_t dt);

private:
	bool created_hole = false;
	bool took_jetpack = false;
};
