#include <cstdint>

#include "util/log.h"

#include "Transform.h"

using namespace crepe;

Transform::Transform(game_object_id_t id, const Point & point, double rot,
					 double scale)
	: Component(id), position(point), rotation(rot), scale(scale) {
	dbg_trace();
}
