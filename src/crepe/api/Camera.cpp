#include "util/Log.h"

#include "Camera.h"
#include "Color.h"
#include "Component.h"

using namespace crepe;

Camera::Camera(game_object_id_t id, const Color & bg_color) : Component(id), bg_color(bg_color) {
	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
