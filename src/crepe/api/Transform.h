#pragma once

#include <cstdint>

#include "api/Point.h"

#include "Component.h"

namespace crepe::api {

class Transform : public Component {
	// FIXME: What's the difference between the `Point` and `Position`
	// classes/structs? How about we replace both with a universal `Vec2` that
	// works similar (or the same) as those found in GLSL?

public:
	Transform(uint32_t id, Point, double, double);
	~Transform();
	int get_instances_max() const;
	//! Translation (shift)
	Point position;
	//! Rotation, in radians
	double rotation;
	//! Multiplication factor
	double scale;
};

} // namespace crepe::api
