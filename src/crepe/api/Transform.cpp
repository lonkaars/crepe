#include "util/log.h"

#include "Transform.h"

using namespace crepe;

Transform::Transform(game_object_id_t id, const Vector2 & point,
					 double rotation, double scale)
	: Component(id),
	  position(point),
	  rotation(rotation),
	  scale(scale) {
	dbg_trace();
}
