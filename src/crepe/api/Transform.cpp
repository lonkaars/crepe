#include "../util/Log.h"

#include "Transform.h"

using namespace crepe;
using namespace std;

Transform::Transform(game_object_id_t id, const vec2 & point, double rotation, double scale)
	: Component(id),
	  position(point),
	  rotation(rotation),
	  scale(scale) {
	dbg_trace();
}

unique_ptr<Component> Transform::save() const {
	return unique_ptr<Component>{new Transform(*this)};
}

void Transform::restore(const Component & snapshot) {
	*this = static_cast<const Transform &>(snapshot);
}

