#pragma once

#include "api/Color.h"
#include "api/GameObject.h"
#include <cstdint>
namespace crepe::api {

class Camera : public GameObject {

public:
	Camera(uint32_t id, std::string name, std::string tag, int layer);
	~Camera();

public:
	Color bg_color; // background color
	double aspect_height, aspect_width; // camera width and height
	double x,y; // camera position
	double zoom;
};
} // namespace crepe::api
