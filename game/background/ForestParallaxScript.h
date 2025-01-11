#pragma once

#include <crepe/api/Script.h>

class ForestParallaxScript : public crepe::Script {
public:
	ForestParallaxScript(float begin_x, float end_x, std::string unique_bg_name);

	void fixed_update(crepe::duration_t dt);

private:
	float begin_x;
	float end_x;
	const std::string name;
	float start_x = 4200;
	const float lenght = 3000;
};
