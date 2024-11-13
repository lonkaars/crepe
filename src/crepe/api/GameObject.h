#pragma once

#include <string>

#include "types.h"
#include "Vector2.h"

namespace crepe {

class ComponentManager;
class BehaviorScript;

/**
 * \brief Represents a GameObject
 * 
 * This class represents a GameObject. The GameObject class is only used
 * as an interface for the game programmer. The actual implementation is
 * done in the ComponentManager.
 */
class GameObject {
private:
	/**
	 * This constructor creates a new GameObject. It creates a new
	 * Transform and Metadata component and adds them to the ComponentManager.
	 * 
	 * \param component_manager Reference to component_manager
	 * \param id The id of the GameObject
	 * \param name The name of the GameObject
	 * \param tag The tag of the GameObject
	 * \param position The position of the GameObject
	 * \param rotation The rotation of the GameObject
	 * \param scale The scale of the GameObject
	 */
	GameObject(ComponentManager & component_manager, game_object_id_t id, const std::string & name, const std::string & tag, const Vector2 & position, double rotation, double scale);
	//! ComponentManager instances GameObject
	friend class ComponentManager;

public:
	/**
	 * \brief Set the parent of this GameObject
	 * 
	 * This method sets the parent of this GameObject. It sets the parent
	 * in the Metadata component of this GameObject and adds this GameObject
	 * to the children list of the parent GameObject.
	 * 
	 * \param parent The parent GameObject
	 */
	void set_parent(const GameObject & parent);
	/**
	 * \brief Add a component to the GameObject
	 * 
	 * This method adds a component to the GameObject. It forwards the
	 * arguments to the ComponentManager.
	 * 
	 * \tparam T The type of the component
	 * \tparam Args The types of the arguments
	 * \param args The arguments to create the component
	 * \return The created component
	 */
	template <typename T, typename... Args>
	T & add_component(Args &&... args);

public:
	//! The id of the GameObject
	const game_object_id_t id;

protected:
	ComponentManager & component_manager;
};

/**
 * \brief Add a BehaviorScript component to this game object
 *
 * The \c BehaviorScript class is the only exception to the ECS harmony, and
 * requires a reference to the component manager passed to its constructor in
 * order to function normally. This is because the \c BehaviorScript (and \c
 * Script) classes are the only component-related classes that store
 * implemented member functions as data.
 */
template <>
BehaviorScript & GameObject::add_component<BehaviorScript>();

} // namespace crepe

#include "GameObject.hpp"
