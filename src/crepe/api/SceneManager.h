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
	/**
	 * \brief Add a new concrete scene to the scene manager
	 *
	 * \tparam T  Type of concrete scene
	 * \param name  Name of new scene
	 */
	template <typename T>
	void add_scene(const std::string & name);
	/**
	 * \brief Set the next scene
	 *
	 * This scene will be loaded at the end of the frame
	 *
	 * \param name  Name of the next scene
	 */
	void set_next_scene(const std::string & name);
	//! Load a new scene (if there is one)
	void load_next_scene();

private:
	SceneManager() = default;

private:
	std::vector<std::unique_ptr<Scene>> scenes;
	std::string next_scene;
};

} // namespace crepe

#include "SceneManager.hpp"
