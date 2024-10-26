#pragma once

#include "Component.h"
#include "api/Color.h"
#include <cstdint>
namespace crepe::api {

class Camera : public Component {

public:
	Camera(uint32_t id, const Color&);
	~Camera();

public:
	Color bg_color; // background color
	double aspect_height, aspect_width; // camera width and height
	double x,y; // camera position
	double zoom;
};
} // namespace crepe::api
