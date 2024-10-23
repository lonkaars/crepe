#pragma once

#include <cstdint>

#include "api/Point.h"

#include "Component.h"

namespace crepe::api {

class Transform : public Component {

public:
	Transform(uint32_t id, Point &, double, double);
	~Transform();
	Point position; // Translation (shift)
	double rotation; // Rotation, in radians
	double scale; // Multiplication factoh
};

} // namespace crepe::api
