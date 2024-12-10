#pragma once

#include "LoopManager.h"

namespace crepe {

template <class T>
void LoopManager::add_scene() {
	this->scene_manager.add_scene<T>();
}

} // namespace crepe
