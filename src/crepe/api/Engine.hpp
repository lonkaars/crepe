#pragma once

#include "Engine.h"

namespace crepe {

template <class T>
void Engine::add_scene() {
	this->scene_manager.add_scene<T>();
}

} // namespace crepe
