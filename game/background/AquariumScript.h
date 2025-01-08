#pragma once

#include <crepe/api/Script.h>

class AquariumScript : public crepe::Script {
public:
	void fixed_update(crepe::duration_t dt);

private:
	float start_x = 10200;
	const float lenght = 3000;
};
