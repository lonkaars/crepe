#include <memory>

#include "../util/log.h"
#include "facade/SDLContext.h"

#include "Component.h"
#include "Sprite.h"
#include "Texture.h"

using namespace std;
using namespace crepe;

Sprite::Sprite(const Component::Data & data, const shared_ptr<Texture> image,
			   const Color & color, const FlipSettings & flip)
	: Component(data),
	  color(color),
	  flip(flip),
	  sprite_image(image) {
	dbg_trace();

	this->sprite_rect.w = sprite_image->get_width();
	this->sprite_rect.h = sprite_image->get_height();
}

Sprite::~Sprite() { dbg_trace(); }
