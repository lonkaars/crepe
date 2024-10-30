

#include "Animator.h"
#include "Component.h"
#include "api/Sprite.h"

#include "util/log.h"
#include <cstdint>

using namespace crepe;
using namespace crepe::api;

Animator::Animator(uint32_t id, Sprite & ss, int row, int col, int row_animator)
	: Component(id), spritesheet(ss), ROW(row), COL(col) , curr_row(row_animator){
	dbg_trace();
	this->count = 0;
}
Animator::~Animator() { dbg_trace(); }
