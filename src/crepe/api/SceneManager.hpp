#include "SceneManager.h"

namespace crepe {

// Add a new concrete scene to the scene manager
template <typename T>
void SceneManager::add_scene(const std::string & name) {
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	scenes.emplace_back(make_unique<T>(name));
}

} // namespace crepe
