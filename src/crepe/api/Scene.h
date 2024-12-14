#pragma once

#include <string>

#include "../manager/ComponentManager.h"
#include "../manager/Mediator.h"
#include "../manager/ResourceManager.h"
#include "../util/Log.h"
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
	virtual std::string get_name() const { return "hoi"; };

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
	SaveManager & get_save_manager() const;

	//! \copydoc ComponentManager::new_object
	GameObject new_object(const std::string & name, const std::string & tag = "",
						  const vec2 & position = {0, 0}, double rotation = 0,
						  double scale = 1);

	//! \copydoc ResourceManager::set_persistent
	void set_persistent(const Asset & asset, bool persistent);
	/**
	* \name Logging functions
	* \see Log
	* \{
	*/
	//! \copydoc Log::logf
	template <class... Args>
	void logf(const Log::Level & level, std::format_string<Args...> fmt, Args &&... args);
	//! \copydoc Log::logf
	template <class... Args>
	void logf(std::format_string<Args...> fmt, Args &&... args);
	//! \}
};

} // namespace crepe

#include "Scene.hpp"
