#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <forward_list>

#include "Component.h"
#include "api/Vector2.h"

namespace crepe {

class GameObject;

/**
 * \brief Manages all components
 * 
 * This class manages all components. It provides methods to add, delete and get
 * components.
 */
class ComponentManager {
public:
	ComponentManager(); // dbg_trace
	~ComponentManager(); // dbg_trace

protected:
	/**
	 * \brief Add a component to the ComponentManager
	 * 
	 * This method adds a component to the ComponentManager. The component is
	 * created with the given arguments and added to the ComponentManager.
	 * 
	 * \tparam T The type of the component
	 * \tparam Args The types of the arguments
	 * \param id The id of the GameObject this component belongs to
	 * \param args The arguments to create the component
	 * \return The created component
	 */
	template <typename T, typename... Args>
	T & add_component(game_object_id_t id, Args &&... args);
	//! GameObject is used as an interface to add components instead of the
	// component manager directly
	friend class GameObject;

public:
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
	 * \brief Get all components of a specific type and id
	 * 
	 * This method gets all components of a specific type and id.
	 * 
	 * \tparam T The type of the component
	 * \param id The id of the GameObject this component belongs to
	 * \return A vector of all components of the specific type and id
	 */
	template <typename T>
	std::vector<std::reference_wrapper<T>>
	get_components_by_id(game_object_id_t id) const;
	/**
	 * \brief Get all components of a specific type
	 * 
	 * This method gets all components of a specific type.
	 * 
	 * \tparam T The type of the component
	 * \return A vector of all components of the specific type
	 */
	template <typename T>
	std::vector<std::reference_wrapper<T>> get_components_by_type() const;

	// TODO: doxygen
	GameObject & new_object(const std::string & name, const std::string & tag = "", const Vector2 & position = { 0, 0 }, double rotation = 0, double scale = 0);

private:
	/**
	 * \brief The components
	 * 
	 * This unordered_map stores all components. The key is the type of the
	 * component and the value is a vector of vectors of unique pointers to the
	 * components.
	 * Every component type has its own vector of vectors of unique pointers to
	 * the components. The first vector is for the ids of the GameObjects and the
	 * second vector is for the components (because a GameObject might have multiple
	 * components).
	 */
	std::unordered_map<std::type_index,
					   std::vector<std::vector<std::unique_ptr<Component>>>>
		components;

	//! ID of next GameObject
	game_object_id_t next_id = 0;
	std::forward_list<std::unique_ptr<GameObject>> objects;
};

} // namespace crepe

#include "ComponentManager.hpp"
