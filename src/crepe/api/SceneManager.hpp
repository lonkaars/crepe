#pragma once

#include "SceneManager.h"

namespace crepe {

template <typename T, typename... Args>
void SceneManager::add_scene(Args &&... args) {
	using namespace std;
	static_assert(is_base_of<Scene, T>::value, "T must be derived from Scene");

	Scene * scene = new T(std::forward<args>(args)...);

	scene->component_manager = this->component_manager;

	this->scenes.emplace_back(unique_ptr<Scene>(scene));

	// The first scene added, is the one that will be loaded at the beginning
	if (next_scene.empty()) {
		next_scene = scene->get_name();
	}
}

} // namespace crepe
