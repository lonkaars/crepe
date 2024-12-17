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
	void add_table(crepe::GameObject & obj, crepe::vec2 offset);
	void add_light(crepe::GameObject & obj, crepe::vec2 offset);
	void add_jetpack_stand(crepe::GameObject & obj, crepe::vec2 offset);
};
