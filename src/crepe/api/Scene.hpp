#pragma once

#include "../util/Log.h"

#include "Scene.h"

namespace crepe {

template <typename... Args>
void Scene::logf(Args &&... args) {
	Log::logf(std::forward<Args>(args)...);
}

} // namespace crepe
