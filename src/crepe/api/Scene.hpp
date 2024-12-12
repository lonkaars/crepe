#pragma once

#include "Scene.h"
#include "../util/Log.h"

namespace crepe {

template <typename... Args>
void Scene::logf(Args &&... args) {
	Log::logf(std::forward<Args>(args)...);
}

}
