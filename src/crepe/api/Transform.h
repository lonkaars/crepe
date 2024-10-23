#pragma once

#include "Component.h"
#include "api/Point.h"
#include <cstdint>
namespace crepe::api {

class Transform : public Component {
public:
	Transform(uint32_t id, Point&, double, double);
	~Transform();
	Point position; // Translation (shift)
	double rotation; // Rotation, in radians
	double scale; // Multiplication factoh
};
} // namespace crepe::api
