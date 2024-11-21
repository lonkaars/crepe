#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "Scene.h"

namespace crepe {

class ComponentManager;

/**
 * \brief Manages scenes
 *
 * This class manages scenes. It can add new scenes and load them. It also manages the current scene
 * and the next scene.
 */
class SceneManager {
public:
	//! \param mgr  Reference to the ComponentManager
	SceneManager(ComponentManager & mgr);

public:
	/**
	 * \brief Add a new concrete scene to the scene manager
	 *
	 * \tparam T  Type of concrete scene
	 * \param name  Name of new scene
	 */
	template <typename T>
	void add_scene();
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
	//! Vector of scenes
	std::vector<std::unique_ptr<Scene>> scenes;
	//! Next scene to load
	std::string next_scene;
	//! Reference to the ComponentManager
	ComponentManager & component_manager;
};

} // namespace crepe

#include "SceneManager.hpp"
