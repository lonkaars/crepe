#include <cstdint>

#include "util/log.h"

#include "Transform.h"

using namespace crepe;

Transform::Transform(uint32_t game_id, const Vector2& point, double rot, double scale)
	: Component(game_id), position(point), rotation(rot), scale(scale) {
	dbg_trace();
}
