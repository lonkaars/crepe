#pragma once

#include "Component.h"
#include "api/Color.h"
#include <cstdint>
namespace crepe {

class BadCamera : public Component {
public:
	BadCamera(uint32_t id) : Component(id), bg_color(api::Color::get_white()) {
		this->x = 0;
		this->y = 0;
		this->zoom = 1;
		this->aspect_width = 480;
		this->aspect_height = 640;
	}
	~BadCamera() {}

public:
	api::Color bg_color; // background color
	double aspect_height, aspect_width; // camera width and height
	double x, y; // camera position
	double zoom;

};
} // namespace crepe
