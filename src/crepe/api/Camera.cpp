#include "types.h"
#include "util/Log.h"

#include "Camera.h"
#include "Color.h"
#include "Component.h"

using namespace crepe;

Camera::Camera(game_object_id_t id, const Color & bg_color, const ivec2 & screen,
			   const vec2 & viewport_size, const double & zoom, const vec2 & offset)
	: Component(id),
	  bg_color(bg_color),
	  offset(offset),
	  screen(screen),
	  viewport_size(viewport_size),
	  zoom(zoom) {
	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
