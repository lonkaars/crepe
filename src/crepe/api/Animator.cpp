
#include "util/Log.h"

#include "Animator.h"
#include "Component.h"
#include "Sprite.h"

using namespace crepe;

Animator::Animator(game_object_id_t id, const Animator::Data & ctx)
	: Component(id),
	  data(ctx) {
	dbg_trace();

	this->data.spritesheet.mask.h /= this->data.col;
	this->data.spritesheet.mask.w /= this->data.row;
	this->data.spritesheet.mask.x = 0;
	this->data.spritesheet.mask.y = this->data.col * this->data.spritesheet.mask.h;

	// need to do this for to get the aspect ratio for a single clipping in the spritesheet
	Sprite & ss = this->data.spritesheet;
	ss.data.aspect_ratio
		= static_cast<double>(this->data.spritesheet.mask.w) / this->data.spritesheet.mask.h;
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
	this->data.curr_row = 0;
	this->data.curr_col = col;
}

void Animator::next_anim() {
	Animator::Data & ctx = this->data;
	ctx.curr_row = ctx.curr_row++ % ctx.row;
	ctx.spritesheet.mask.x = ctx.curr_row * ctx.spritesheet.mask.w;
}
