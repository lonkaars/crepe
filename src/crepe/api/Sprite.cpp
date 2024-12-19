#include <cmath>

#include "../util/dbg.h"
#include "api/Asset.h"

#include "Component.h"
#include "Sprite.h"
#include "types.h"

using namespace std;
using namespace crepe;

Sprite::Sprite(game_object_id_t id, const Asset & texture, const Sprite::Data & data)
	: Component(id),
	  source(texture),
	  data(data) {

	dbg_trace();
}

Sprite::~Sprite() { dbg_trace(); }
