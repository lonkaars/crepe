#pragma once

#include <crepe/api/Script.h>

class HallwayScript : public crepe::Script {
public:
	void fixed_update(crepe::duration_t dt);

private:
	float start_x = 1200;
	const float lenght = 3000;
	int current_sector = 2;
};
