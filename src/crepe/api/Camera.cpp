#include "types.h"
#include "util/Log.h"

#include "Camera.h"
#include "Component.h"

using namespace crepe;

Camera::Camera(game_object_id_t id, const ivec2 & screen, const vec2 & viewport_size,
			   const Data & ctx)
	: Component(id),
	  screen(screen),
	  viewport_size(viewport_size),
	  data(ctx) {
	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
