#pragma once

#include <string>

namespace crepe {

class SceneManager;
class ComponentManager;

/**
 * \brief Represents a Scene
 * 
 * This class represents a Scene. The Scene class is only used as an interface for the game
 * programmer.
 */
class Scene {
protected:
	/**
	 * \param mgr  Reference to the ComponentManager
	 * \param name  Name of the scene
	 */
	Scene(ComponentManager & mgr, const std::string & name);
	//! SceneManager instances Scene
	friend class SceneManager;

public:
	virtual ~Scene() = default;

public:
	//! Load the scene
	virtual void load_scene() = 0;
	//! The scene name
	const std::string name;

protected:
	//! Reference to the ComponentManager
	ComponentManager & component_manager;
};

} // namespace crepe
