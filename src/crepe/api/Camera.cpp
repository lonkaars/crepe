#include "util/log.h"

#include "Camera.h"
#include "Color.h"
#include "Component.h"

using namespace crepe;

Camera::Camera(const Component::Data & data, const Color & bg_color)
	: Component(data),
	  bg_color(bg_color) {
	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
