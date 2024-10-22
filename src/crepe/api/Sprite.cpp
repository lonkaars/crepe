

#include "Sprite.h"
#include "api/Texture.h"
#include "util/log.h"
#include <memory>
#include <utility>

using namespace std;
using namespace crepe;
using namespace crepe::api;

Sprite::Sprite(unique_ptr<Texture> image, const Color & color,
			   const flip_settings & flip) : color(color), flip(flip), sprite_image(std::move(image)) {
	dbg_trace();
}

Sprite::~Sprite() { dbg_trace(); }
