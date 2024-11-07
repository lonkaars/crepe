#pragma once

#include <cstdint>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Component.h"

namespace crepe {

/**
 * \brief Manages all components
 * 
 * This class manages all components. It provides methods to add, delete and get
 * components.
 */
class ComponentManager {
public:
	/**
	 * \brief Get the instance of the ComponentManager
	 * 
	 * \return The instance of the ComponentManager
	 */
	static ComponentManager & get_instance();
	ComponentManager(const ComponentManager &) = delete;
	ComponentManager(ComponentManager &&) = delete;
	ComponentManager & operator=(const ComponentManager &) = delete;
	ComponentManager & operator=(ComponentManager &&) = delete;
	~ComponentManager();

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

private:
	ComponentManager();

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
};

} // namespace crepe

#include "ComponentManager.hpp"
