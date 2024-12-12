
#include "util/Log.h"

#include "Animator.h"
#include "Component.h"
#include "Sprite.h"

using namespace crepe;

Animator::Animator(game_object_id_t id, Sprite & spritesheet, const ivec2 & single_frame_size,
				   const uvec2 & grid_size, const Animator::Data & data)
	: Component(id),
	  spritesheet(spritesheet),
	  grid_size(grid_size),
	  data(data) {
	dbg_trace();

	this->spritesheet.mask.w = single_frame_size.x;
	this->spritesheet.mask.h = single_frame_size.y;
	this->spritesheet.mask.x = 0;
	this->spritesheet.mask.y = 0;

	this->spritesheet.aspect_ratio
		= static_cast<float>(single_frame_size.x) / single_frame_size.y;
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
	ctx.row = ctx.row++ % this->grid_size.x;
	this->spritesheet.mask.x = ctx.row * this->spritesheet.mask.w;
}
