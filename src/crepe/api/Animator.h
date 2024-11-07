#pragma once

#include "Component.h"
#include "api/Sprite.h"
#include <cstdint>


namespace crepe {
	class AnimatorSystem;
}
namespace crepe::api {

class Animator : public Component {


public:
	void loop();
	void stop();

public:
	Animator(uint32_t id, Sprite&, int row, int col, int row_animate);
	virtual ~Animator();

private:
	Sprite& spritesheet;
	const int COL,ROW;
	int curr_row;
	int count;
	int fps;

private:
	friend class crepe::AnimatorSystem;
};
} // namespace crepe::api
