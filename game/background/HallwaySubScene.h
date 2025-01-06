#pragma once

#include <crepe/types.h>

namespace crepe {
class Scene;
class GameObject;
class Color;
} // namespace crepe

class HallwaySubScene {
public:
	float create(
		crepe::Scene & scn, float begin_x, unsigned int sector_num, crepe::Color sector_color
	);

private:
	void add_lamp(crepe::GameObject & obj, crepe::vec2 offset, unsigned int fps = 10);

	void add_sector_number(
		crepe::GameObject & obj, crepe::vec2 offset, unsigned int sector_num,
		crepe::Color sector_color
	);
};
