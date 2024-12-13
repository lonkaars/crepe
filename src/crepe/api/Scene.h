#pragma once

#include <string>

#include "../manager/ComponentManager.h"
#include "../manager/Mediator.h"
#include "../manager/ResourceManager.h"
#include "../util/OptionalRef.h"

#include "GameObject.h"

namespace crepe {

class SceneManager;
class ComponentManager;
class Asset;

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

private:
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

protected:
	/**
	* \brief Retrieve the reference to the SaveManager instance
	*
	* \returns A reference to the SaveManager instance held by the Mediator.
	*/
	SaveManager & get_save_manager() const { return mediator->save_manager; }

	/**
	 * \brief Create a new game object using the component manager
	 *
	 * \param name Metadata::name (required)
	 * \param tag Metadata::tag (optional, empty by default)
	 * \param position Transform::position (optional, origin by default)
	 * \param rotation Transform::rotation (optional, 0 by default)
	 * \param scale Transform::scale (optional, 1 by default)
	 *
	 * \returns GameObject interface
	 *
	 * \note This method automatically assigns a new entity ID
	 */
	GameObject new_object(const std::string & name, const std::string & tag = "",
						  const vec2 & position = {0, 0}, double rotation = 0,
						  double scale = 1) {
		// Forward the call to ComponentManager's new_object method
		return mediator->component_manager->new_object(name, tag, position, rotation, scale);
	}

	/**
	 * \brief Mark a resource as persistent (i.e. used across multiple scenes)
	 *
	 * \param asset Asset the concrete resource is instantiated from
	 * \param persistent Whether this resource is persistent (true=keep, false=destroy)
	 */
	void set_persistent(const Asset & asset, bool persistent) {
		mediator->resource_manager->set_persistent(asset, persistent);
	}

	/**
	 * \brief Log a message using Log::logf
	 *
	 * \tparam Args Log::logf parameters
	 * \param args  Log::logf parameters
	 */
	template <typename... Args>
	void logf(Args &&... args);
};

} // namespace crepe

#include "Scene.hpp"
