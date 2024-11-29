#include <cmath>
#include <utility>

#include "../util/Log.h"

#include "Component.h"
#include "Sprite.h"
#include "Texture.h"

using namespace std;
using namespace crepe;

Sprite::Sprite(game_object_id_t id, Texture & image, const Color & color,
			   const FlipSettings & flip, int sort_layer, int order_layer, float height)
	: Component(id),
	  color(color),
	  flip(flip),
	  sprite_image(std::move(image)),
	  sorting_in_layer(sort_layer),
	  order_in_layer(order_layer),
	  height(height) {

	dbg_trace();

	this->mask.w = sprite_image.get_width();
	this->mask.h = sprite_image.get_height();
	this->aspect_ratio = static_cast<double>(this->mask.w) / this->mask.h;
}

Sprite::~Sprite() { dbg_trace(); }
