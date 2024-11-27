#include "util/Log.h"

#include "Camera.h"
#include "Color.h"
#include "Component.h"

using namespace crepe;

Camera::Camera(game_object_id_t id, const Color & bg_color, const ivec2 & screen,
			   const ivec2 & viewport, const double & zoom)
	: Component(id),
	  bg_color(bg_color),
	  screen(screen),
	  viewport(viewport),
	  zoom(zoom) {
	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
