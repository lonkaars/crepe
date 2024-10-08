#pragma once

#include "api/Component.h"
#include "api/Point.h"
namespace crepe::api {

class Transform : public Component {
public:
	Point position; // Translation (shift)
	double rotation; // Rotation, in radians
	double scale; // Multiplication factoh
};
} // namespace crepe::api
