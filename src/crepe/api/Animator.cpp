
#include <cstdint>

#include "util/log.h"

#include "Component.h"
#include "Sprite.h"
#include "Animator.h"

using namespace crepe;

Animator::Animator(uint32_t id, Sprite & ss, int row, int col, int col_animator)
	: Component(id), spritesheet(ss), row(row), col(col){
	dbg_trace();

	animator_rect = spritesheet.sprite_rect;
	animator_rect.h /= col;
	animator_rect.w /= row;
	animator_rect.x = 0;
	animator_rect.y = col_animator * animator_rect.h;
	this->active = false;
}
Animator::~Animator() { dbg_trace(); }