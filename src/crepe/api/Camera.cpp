
#include <cstdint>

#include "util/log.h"

#include "Component.h"
#include "Color.h"
#include "Camera.h"

using namespace crepe;

Camera::Camera(uint32_t id, const Color & color)
	: Component(id), bg_color(color), aspect_width(640), aspect_height(480),
	  zoom(1), x(0), y(0) {
	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
