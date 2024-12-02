
#include "util/Log.h"

#include "Animator.h"
#include "Component.h"
#include "Sprite.h"

using namespace crepe;

Animator::Animator(game_object_id_t id, Sprite & ss, int row, int col, int col_animator)
	: Component(id),
	  spritesheet(ss),
	  row(row),
	  col(col) {
	dbg_trace();

	this->spritesheet.mask.h /= col;
	this->spritesheet.mask.w /= row;
	this->spritesheet.mask.x = 0;
	this->spritesheet.mask.y = col_animator * this->spritesheet.mask.h;

	// need to do this for to get the aspect ratio for a single clipping in the spritesheet
	this->spritesheet.aspect_ratio
		= static_cast<double>(this->spritesheet.mask.w) / this->spritesheet.mask.h;
}
Animator::~Animator() { dbg_trace(); }

void Animator::loop() { this->looping = true; }
void Animator::play() { this->active = true; }
void Animator::pause() { this->active = false; }
void Animator::stop() {
	this->active = false;
	this->curr_col = 0;
	this->curr_row = 0;
}
void Animator::set_fps(int fps) { this->fps = fps; }
void Animator::set_cycle_range(int start, int end) {
	this->cycle_start = start, this->cycle_end = end;
}
void Animator::set_anim(int col) {
	this->curr_row = 0;
	this->curr_col = col;
}
