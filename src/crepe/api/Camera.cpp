

#include "Camera.h"
#include "api/Color.h"
#include "api/GameObject.h"
#include "fix_camera.h"
#include "util/log.h"

using namespace crepe::api;

Camera::Camera(uint32_t id, std::string name, std::string tag, int layer)
	: GameObject(id, name, tag, layer), bg_color(Color::get_black()) {
	dbg_trace();

	this->add_component<BadCamera>();
}

Camera::~Camera() { dbg_trace(); }
