#pragma once

#include <crepe/types.h>

namespace crepe {
class Scene;
class GameObject;
} // namespace crepe

class AquariumSubScene {
public:
	float create(crepe::Scene & scn, float begin_x);

private:
	void add_background(crepe::Scene & scn, float begin_x);
	void
	add_bubbles(crepe::GameObject & obj, crepe::vec2 offset, int order_in_layer, float scale);
};
