#pragma once

namespace crepe {
class Scene;
}

class Aquarium {
public:
	float create(crepe::Scene & scn, float begin_x);

private:
	void add_background(crepe::Scene & scn, float begin_x);
};
