

#include "Animator.h"
#include "Component.h"
#include "api/Sprite.h"

#include "util/log.h"
#include <cstdint>

using namespace crepe;

Animator::Animator(uint32_t id, Sprite & ss, int row, int col, int row_animator)
	: Component(id), spritesheet(ss), ROW(row), COL(col) , curr_row(row_animator){
	dbg_trace();
	ss.sprite_rect.y = row * ss.sprite_rect.h;
	ss.sprite_rect.x = 0;
}
Animator::~Animator() { dbg_trace(); }
