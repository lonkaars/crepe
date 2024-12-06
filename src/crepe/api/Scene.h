#pragma once

#include <string>

#include "../manager/Mediator.h"
#include "../util/OptionalRef.h"

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

	// TODO: Late references should ALWAYS be private! This is currently kept as-is so unit tests
	// keep passing, but this reference should not be directly accessible by the user!!!

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
	//! Mediator reference
	OptionalRef<Mediator> mediator;
	//! \}
};

} // namespace crepe
