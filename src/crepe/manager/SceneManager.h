#pragma once

#include <memory>
#include <vector>

#include "../api/Scene.h"

#include "Manager.h"

namespace crepe {

class ComponentManager;

/**
 * \brief Manages scenes
 *
 * This class manages scenes. It can add new scenes and load them. It also manages the current scene
 * and the next scene.
 */
class SceneManager : public Manager {
public:
	SceneManager(Mediator & mediator);

public:
	/**
	 * \brief Add a new concrete scene to the scene manager
	 *
	 * \tparam T  Type of concrete scene
	 */
	template <typename T, typename... Args>
	void add_scene(Args &&... args);
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
	//! Vector of concrete scenes (added by add_scene())
	std::vector<std::unique_ptr<Scene>> scenes;
	//! Next scene to load
	std::string next_scene;
};

} // namespace crepe

#include "SceneManager.hpp"
