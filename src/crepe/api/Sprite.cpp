#include <cmath>

#include "../util/Log.h"
#include "api/Asset.h"

#include "Component.h"
#include "Sprite.h"
#include "types.h"

using namespace std;
using namespace crepe;

Sprite::Sprite(game_object_id_t id, const Asset & texture, const ivec2 & size, const Sprite::Data & data)
	: Component(id),
	  source(texture),
	  data(data) {

	dbg_trace();

	this->mask.w = size.x;
	this->mask.h = size.y;
	this->aspect_ratio = static_cast<double>(this->mask.w) / this->mask.h;
}

Sprite::~Sprite() { dbg_trace(); }
