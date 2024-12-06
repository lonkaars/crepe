#include <cmath>
#include <utility>

#include "../util/Log.h"

#include "Component.h"
#include "Sprite.h"
#include "Texture.h"
#include "types.h"

using namespace std;
using namespace crepe;

Sprite::Sprite(game_object_id_t id, Texture & texture, const Sprite::Data & ctx)
	: Component(id),
	  texture(std::move(texture)),
	  data(ctx) {

	dbg_trace();

	this->mask.w = this->texture.get_size().x;
	this->mask.h = this->texture.get_size().y;
	this->aspect_ratio = static_cast<double>(this->mask.w) / this->mask.h;
}

Sprite::~Sprite() { dbg_trace(); }
