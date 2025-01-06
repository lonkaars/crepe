#pragma once

#include <crepe/api/Script.h>

class ForestParallaxScript : public crepe::Script {
public:
	ForestParallaxScript(float begin_x, float end_x, std::string unique_bg_name);

	void fixed_update(crepe::duration_t dt);

private:
	const float begin_x;
	const float end_x;
	const std::string name;
};
