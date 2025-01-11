#pragma once

#include <string>

namespace crepe {
class Scene;
}

class ForestSubScene {
public:
	float create(crepe::Scene & scn, float begin_x, std::string unique_bg_name);

private:
	void add_background(crepe::Scene & scn, float begin_x, std::string name);
};
