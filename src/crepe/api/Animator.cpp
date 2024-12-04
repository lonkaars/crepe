
#include "util/Log.h"

#include "Animator.h"
#include "Component.h"
#include "Sprite.h"

using namespace crepe;

Animator::Animator(uint32_t id, Sprite & ss, int max_row, int max_col,
				   const Animator::Data & ctx)
	: Component(id),
	  spritesheet(ss),
	  row(max_row),
	  col(max_col),
	  data(ctx) {
	dbg_trace();

	this->spritesheet.mask.h /= this->col;
	this->spritesheet.mask.w /= this->row;
	this->spritesheet.mask.x = this->data.curr_row * this->spritesheet.mask.w;
	this->spritesheet.mask.y = this->data.curr_col * this->spritesheet.mask.h;

	// need to do this for to get the aspect ratio for a single clipping in the spritesheet
	this->spritesheet.aspect_ratio
		= static_cast<double>(this->spritesheet.mask.w) / this->spritesheet.mask.h;
}

Animator::~Animator() { dbg_trace(); }

void Animator::loop() { this->data.looping = true; }

void Animator::play() { this->active = true; }

void Animator::pause() { this->active = false; }

void Animator::stop() {
	this->active = false;
	this->data.curr_col = 0;
	this->data.curr_row = 0;
}
void Animator::set_fps(int fps) { this->data.fps = fps; }

void Animator::set_cycle_range(int start, int end) {
	this->data.cycle_start = start, this->data.cycle_end = end;
}

void Animator::set_anim(int col) {
	Animator::Data & ctx = this->data;
	this->spritesheet.mask.x = ctx.curr_row = 0;
	ctx.curr_col = col;
	this->spritesheet.mask.y = ctx.curr_col * this->spritesheet.mask.h;
}

void Animator::next_anim() {
	Animator::Data & ctx = this->data;
	ctx.curr_row = ctx.curr_row++ % this->row;
	this->spritesheet.mask.x = ctx.curr_row * this->spritesheet.mask.w;
}
