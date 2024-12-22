
#include "util/dbg.h"

#include "Animator.h"
#include "Component.h"
#include "Sprite.h"

using namespace crepe;

Animator::Animator(
	game_object_id_t id, Sprite & spritesheet, const ivec2 & single_frame_size,
	const uvec2 & grid_size, const Animator::Data & data
)
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
	this->data.frame = this->data.cycle_start;
}
void Animator::set_fps(int fps) { this->data.fps = fps; }

void Animator::set_cycle_range(int start, int end) {
	this->data.cycle_start = start;
	this->data.cycle_end = end;
}
