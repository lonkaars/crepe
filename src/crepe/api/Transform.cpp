#include "util/log.h"

#include "Transform.h"

using namespace crepe;

Transform::Transform(const Component::Data & data, const Vector2 & point,
					 double rotation, double scale)
	: Component(data),
	  position(point),
	  rotation(rotation),
	  scale(scale) {
	dbg_trace();
}
