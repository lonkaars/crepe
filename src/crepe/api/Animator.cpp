
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

	this->spritesheet.sprite_rect.h /= col;
	this->spritesheet.sprite_rect.w /= row;
	this->spritesheet.sprite_rect.x = 0;
	this->spritesheet.sprite_rect.y = col_animator * this->spritesheet.sprite_rect.h;
	this->active = false;

	// need to do this for to get the aspect ratio for a single clipping in the spritesheet
	this->spritesheet.aspect_ratio = static_cast<double>(this->spritesheet.sprite_rect.w)
									 / this->spritesheet.sprite_rect.h;
}
Animator::~Animator() { dbg_trace(); }
