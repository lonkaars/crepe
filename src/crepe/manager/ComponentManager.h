#pragma once

#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "../Component.h"
#include "../types.h"

#include "Manager.h"

namespace crepe {

class GameObject;

/**
 * \brief Manages all components
 *
 * This class manages all components. It provides methods to add, delete and get components.
 */
class ComponentManager : public Manager {
	// TODO: This relation should be removed! I (loek) believe that the scene manager should
	// create/destroy components because the GameObject's are stored in concrete Scene classes,
	// which will in turn call GameObject's destructor, which will in turn call
	// ComponentManager::delete_components_by_id or something. This is a pretty major change, so
	// here is a comment and temporary fix instead :tada:
	friend class SceneManager;

public:
	ComponentManager(Mediator & mediator);
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
	/**
	 * \brief Get all components of a specific type on a GameObject with name \c name
	 * 
	 * \tparam T The type of the component
	 * \param name Metadata::name for the same game_object_id as the returned components
	 * \return Components matching criteria
	 */
	template <typename T>
	RefVector<T> get_components_by_name(const std::string & name) const;
	/**
	 * \brief Get all components of a specific type on a GameObject with tag \c tag
	 * 
	 * \tparam T The type of the component
	 * \param name Metadata::tag for the same game_object_id as the returned components
	 * \return Components matching criteria
	 */
	template <typename T>
	RefVector<T> get_components_by_tag(const std::string & tag) const;

private:
	/**
	 * \brief Get object IDs by predicate function
	 *
	 * This function calls the predicate function \c pred for all components matching type \c T,
	 * and adds their parent game_object_id to a \c std::set if the predicate returns true.
	 *
	 * \tparam T The type of the component to check the predicate against
	 * \param pred Predicate function
	 *
	 * \note The predicate function may be called for multiple components with the same \c
	 * game_object_id. In this case, the ID is added if *any* call returns \c true.
	 *
	 * \returns game_object_id for all components where the predicate returned true
	 */
	template <typename T>
	std::set<game_object_id_t>
	get_objects_by_predicate(const std::function<bool(const T &)> & pred) const;

	/**
	 * \brief Get components of type \c T for multiple game object IDs
	 *
	 * \tparam T The type of the components to return
	 * \param ids The object IDs
	 *
	 * \return All components matching type \c T and one of the IDs in \c ids
	 */
	template <typename T>
	RefVector<T> get_components_by_ids(const std::set<game_object_id_t> & ids) const;

	/**
	 * \brief Get object IDs for objects with name \c name
	 *
	 * \param name Object name to match
	 * \returns Object IDs where Metadata::name is equal to \c name
	 */
	std::set<game_object_id_t> get_objects_by_name(const std::string & name) const;
	/**
	 * \brief Get object IDs for objects with tag \c tag
	 *
	 * \param tag Object tag to match
	 * \returns Object IDs where Metadata::tag is equal to \c tag
	 */
	std::set<game_object_id_t> get_objects_by_tag(const std::string & tag) const;

private:
	//! By Component \c std::type_index (readability helper type)
	template <typename T>
	using by_type = std::unordered_map<std::type_index, T>;
	//! By \c game_object_id index (readability helper type)
	template <typename T>
	using by_id_index = std::vector<T>;
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
	by_type<by_id_index<std::vector<std::unique_ptr<Component>>>> components;

	//! Persistent flag for each GameObject
	std::unordered_map<game_object_id_t, bool> persistent;

	//! ID of next GameObject allocated by \c ComponentManager::new_object
	game_object_id_t next_id = 0;
};

} // namespace crepe

#include "ComponentManager.hpp"
