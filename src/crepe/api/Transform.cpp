#include "../util/Log.h"

#include "Transform.h"

using namespace crepe;

Transform::Transform(game_object_id_t id, const vec2 & point, double rotation, double scale)
	: Component(id),
	  position(point),
	  rotation(rotation),
	  scale(scale) {
	dbg_trace();
}
