#include "SceneManager.h"

using namespace crepe;
using namespace std;

// Add a new concrete scene to the scene manager
template <typename T>
void SceneManager::add_scene(string name) {
	static_assert(is_base_of<Scene, T>::value, "T must be derived from Scene");
	scenes.emplace_back(make_unique<T>(name));
}
