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
	//TODO: Use Loek's custom reference class to set ComponentManger via SceneManager instead of via constructor
	/**
	 * \param mgr  Reference to the ComponentManager
	 */
	Scene(ComponentManager & mgr);
	//! SceneManager instances Scene
	friend class SceneManager;

public:
	virtual ~Scene() = default;

public:
	//! Load the scene
	virtual void load_scene() = 0;
	/**
	 * \brief Get the scene's name
	 * \return The scene's name
	 */
	virtual std::string get_name() const = 0;

protected:
	//! Reference to the ComponentManager
	ComponentManager & component_manager;
};

} // namespace crepe
