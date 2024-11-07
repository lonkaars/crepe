#pragma once

#include "Component.h"
#include "api/Sprite.h"
#include <cstdint>

namespace crepe {

class Animator : public Component {

public:
	void loop();
	void stop();

public:
	Animator(uint32_t id, Sprite &, int row, int col, int row_animate);
	~Animator();

private:
	Sprite & spritesheet;
	const int COL, ROW;
	int curr_row = 0;
	int count = 0;

	int fps;

private:
	friend class AnimatorSystem;
};
} // namespace crepe
