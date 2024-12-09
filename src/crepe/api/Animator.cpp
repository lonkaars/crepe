
#include "util/Log.h"

#include "Animator.h"
#include "Component.h"
#include "Sprite.h"

using namespace crepe;

Animator::Animator(game_object_id_t id, Sprite & spritesheet, unsigned int pixel_frame_x,
				   unsigned int pixel_frame_y, unsigned int max_row, unsigned int max_col,
				   const Animator::Data & data)
	: Component(id),
	  spritesheet(spritesheet),
	  max_rows(max_row),
	  max_columns(max_col),
	  data(data) {
	dbg_trace();

	this->spritesheet.mask.h = this->max_columns * pixel_frame_y;
	this->spritesheet.mask.w /= this->max_rows * pixel_frame_x;
	this->spritesheet.mask.x = this->data.row * this->spritesheet.mask.w;
	this->spritesheet.mask.y = this->data.col * this->spritesheet.mask.h;
}

Animator::~Animator() { dbg_trace(); }

void Animator::loop() { this->data.looping = true; }

void Animator::play() { this->active = true; }

void Animator::pause() { this->active = false; }

void Animator::stop() {
	this->active = false;
	this->data.col = 0;
	this->data.row = 0;
}
void Animator::set_fps(int fps) { this->data.fps = fps; }

void Animator::set_cycle_range(int start, int end) {
	this->data.cycle_start = start, this->data.cycle_end = end;
}

void Animator::set_anim(int col) {
	Animator::Data & ctx = this->data;
	this->spritesheet.mask.x = ctx.row = 0;
	ctx.col = col;
	this->spritesheet.mask.y = ctx.col * this->spritesheet.mask.h;
}

void Animator::next_anim() {
	Animator::Data & ctx = this->data;
	ctx.row = ctx.row++ % this->max_rows;
	this->spritesheet.mask.x = ctx.row * this->spritesheet.mask.w;
}
