#pragma once

#include <crepe/types.h>

namespace crepe {
class Scene;
class GameObject;
} // namespace crepe

class Start {
public:
	float create(crepe::Scene & scn, float begin_x);

private:
	void add_lamp(crepe::GameObject & obj, crepe::vec2 offset, unsigned int fps = 10);
};
