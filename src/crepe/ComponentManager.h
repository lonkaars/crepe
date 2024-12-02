#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Component.h"
#include "types.h"

namespace crepe {

class GameObject;

/**
 * \brief Manages all components
 * 
 * This class manages all components. It provides methods to add, delete and get components.
 */
class ComponentManager {
	// TODO: This relation should be removed! I (loek) believe that the scene manager should
	// create/destroy components because the GameObject's are stored in concrete Scene classes,
	// which will in turn call GameObject's destructor, which will in turn call
	// ComponentManager::delete_components_by_id or something. This is a pretty major change, so
	// here is a comment and temporary fix instead :tada:
	friend class SceneManager;

public:
	ComponentManager(); // dbg_trace
	~ComponentManager(); // dbg_trace

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
						  double scale = 1);

protected:
	/**
	 * GameObject is used as an interface to add/remove components, and the game programmer is
	 * supposed to use it instead of interfacing with the component manager directly.
	 */
	friend class GameObject;
	/**
	 * \brief Add a component to the ComponentManager
	 * 
	 * This method adds a component to the ComponentManager. The component is created with the
	 * given arguments and added to the ComponentManager.
	 * 
	 * \tparam T The type of the component
	 * \tparam Args The types of the arguments
	 * \param id The id of the GameObject this component belongs to
	 * \param args The arguments to create the component
	 * \return The created component
	 */
	template <typename T, typename... Args>
	T & add_component(game_object_id_t id, Args &&... args);
	/**
	 * \brief Delete all components of a specific type and id
	 * 
	 * This method deletes all components of a specific type and id.
	 * 
	 * \tparam T The type of the component
	 * \param id The id of the GameObject this component belongs to
	 */
	template <typename T>
	void delete_components_by_id(game_object_id_t id);
	/**
	 * \brief Delete all components of a specific type
	 * 
	 * This method deletes all components of a specific type.
	 * 
	 * \tparam T The type of the component
	 */
	template <typename T>
	void delete_components();
	/**
	 * \brief Delete all components of a specific id
	 * 
	 * This method deletes all components of a specific id.
	 * 
	 * \param id The id of the GameObject this component belongs to
	 */
	void delete_all_components_of_id(game_object_id_t id);
	/**
	 * \brief Delete all components
	 * 
	 * This method deletes all components.
	 */
	void delete_all_components();
	/**
	 * \brief Set a GameObject as persistent
	 *
	 * This method sets a GameObject as persistent. If a GameObject is persistent, its
	 * components will not be deleted.
	 *
	 * \param id The id of the GameObject to set as persistent
	 * \param persistent The persistent flag
	 */
	void set_persistent(game_object_id_t id, bool persistent);

public:
	/**
	 * \brief Get all components of a specific type and id
	 * 
	 * This method gets all components of a specific type and id.
	 * 
	 * \tparam T The type of the component
	 * \param id The id of the GameObject this component belongs to
	 * \return A vector of all components of the specific type and id
	 */
	template <typename T>
	RefVector<T> get_components_by_id(game_object_id_t id) const;
	/**
	 * \brief Get all components of a specific type
	 * 
	 * This method gets all components of a specific type.
	 * 
	 * \tparam T The type of the component
	 * \return A vector of all components of the specific type
	 */
	template <typename T>
	RefVector<T> get_components_by_type() const;

private:
	/**
	 * \brief The components
	 * 
	 * This unordered_map stores all components. The key is the type of the component and the
	 * value is a vector of vectors of unique pointers to the components.
	 *
	 * Every component type has its own vector of vectors of unique pointers to the components.
	 * The first vector is for the ids of the GameObjects and the second vector is for the
	 * components (because a GameObject might have multiple components).
	 */
	std::unordered_map<std::type_index, std::vector<std::vector<std::unique_ptr<Component>>>>
		components;

	//! Persistent flag for each GameObject
	std::unordered_map<game_object_id_t, bool> persistent;

	//! ID of next GameObject allocated by \c ComponentManager::new_object
	game_object_id_t next_id = 0;
};

} // namespace crepe

#include "ComponentManager.hpp"
