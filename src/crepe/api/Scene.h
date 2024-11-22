#pragma once

#include "util/OptionalRef.h"
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
	// NOTE: This must be the only constructor on Scene, see "Late references" below
	Scene() = default;
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
	/**
	 * \name Late references
	 * 
	 * These references are set by SceneManager immediately after calling the constructor of Scene.
	 *
	 * \note Scene must have a constructor without arguments so the game programmer doesn't need to
	 * manually add `using Scene::Scene` to their concrete scene class, if they want to add a
	 * constructor with arguments (e.g. for passing references to their own concrete Scene classes).
	 *
	 * \{
	 */
	//! Reference to the ComponentManager
	OptionalRef<ComponentManager> component_manager;
	//! \}
};

} // namespace crepe
