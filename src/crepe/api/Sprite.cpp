#include <cmath>

#include "../util/Log.h"

#include "Component.h"
#include "Sprite.h"
#include "Texture.h"

using namespace std;
using namespace crepe;

Sprite::Sprite(game_object_id_t id, const Texture & image, const Color & color,
			   const FlipSettings & flip, uint8_t sort_layer, uint8_t order_layer, int height)
	: Component(id),
	  color(color),
	  flip(flip),
	  sprite_image(image),
	  sorting_in_layer(sort_layer),
	  order_in_layer(order_layer),
	  height(height) {

	dbg_trace();

	this->sprite_rect.w = sprite_image.get_width();
	this->sprite_rect.h = sprite_image.get_height();
	this->aspect_ratio = static_cast<double>(this->sprite_rect.w) / this->sprite_rect.h;
}

Sprite::~Sprite() { dbg_trace(); }
