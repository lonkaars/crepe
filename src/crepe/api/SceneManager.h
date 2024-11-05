#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "Scene.h"

namespace crepe {

class SceneManager {
public:
	// Singleton
	static SceneManager & get_instance();
	SceneManager(const SceneManager &) = delete;
	SceneManager(SceneManager &&) = delete;
	SceneManager & operator=(const SceneManager &) = delete;
	SceneManager & operator=(SceneManager &&) = delete;

public:
	template <typename T>
	void add_scene(std::string name);
	void load_scene(std::string name);
	void empty_queue();

private:
	SceneManager();

private:
	std::vector<std::unique_ptr<Scene>> scenes;
	std::queue<std::string> next_scene;
};

} // namespace crepe

#include "SceneManager.hpp"
