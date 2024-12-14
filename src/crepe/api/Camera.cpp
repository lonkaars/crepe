#include "util/dbg.h"

#include "Camera.h"
#include "Component.h"
#include "types.h"

using namespace crepe;

Camera::Camera(game_object_id_t id, const vec2 & viewport_size, const Data & data)
	: Component(id),
	  viewport_size(viewport_size),
	  data(data) {
	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
