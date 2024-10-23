

#include "Transform.h"
#include "api/Point.h"
#include "util/log.h"

using namespace crepe::api;

Transform::Transform(Point & point, double rot, double scale)
	: position(point), rotation(rot), scale(scale) {
	dbg_trace();
}
Transform::~Transform() { dbg_trace(); }
