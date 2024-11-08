#pragma once

#include <cstdint>

#include "api/Point.h"

#include "Component.h"

namespace crepe {

/**
 * \brief Transform Component that will be present the gameobject position, rotation and scale.
 *
 * This transform component will automatically be made with each gameobject
 */
class Transform : public Component {
	// FIXME: What's the difference between the `Point` and `Position`
	// classes/structs? How about we replace both with a universal `Vec2` that
	// works similar (or the same) as those found in GLSL?

public:
	Transform(uint32_t id, const Point &, double, double);
	~Transform();
	virtual int get_instances_max() const { return 1; }
	//! Translation (shift)
	Point position;
	//! Rotation, in radians
	double rotation;
	//! Multiplication factor
	double scale;
};

} // namespace crepe
