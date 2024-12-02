#include "types.h"
#include "util/Log.h"

#include "Camera.h"
#include "Component.h"

using namespace crepe;

Camera::Camera(game_object_id_t id, const Data & ctx) : Component(id), data(ctx) {

	dbg_trace();
}

Camera::~Camera() { dbg_trace(); }
