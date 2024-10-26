

#include "Camera.h"
#include "Component.h"
#include "api/Color.h"
#include "util/log.h"
#include <cstdint>

using namespace crepe::api;

Camera::Camera(uint32_t id, const Color& color) : Component(id), bg_color(color), aspect_width(640), aspect_height(480), zoom(1), x(0),y(0){
	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
