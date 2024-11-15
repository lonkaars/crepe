#pragma once

#include <string>

#include "types.h"

namespace crepe {

class Vector2;

/**
 * \brief Represents a GameObject
 * 
 * This class represents a GameObject. The GameObject class is only used as an interface for
 * the game programmer. The actual implementation is done in the ComponentManager.
 */
class GameObject {
public:
	/**
	 * This constructor creates a new GameObject. It creates a new Transform and Metadata
	 * component and adds them to the ComponentManager.
	 * 
	 * \param id The id of the GameObject
	 * \param name The name of the GameObject
	 * \param tag The tag of the GameObject
	 * \param position The position of the GameObject
	 * \param rotation The rotation of the GameObject
	 * \param scale The scale of the GameObject
	 */
	GameObject(game_object_id_t id, const std::string & name, const std::string & tag,
			   const Vector2 & position, double rotation, double scale);
	/**
	 * \brief Set the parent of this GameObject
	 * 
	 * This method sets the parent of this GameObject. It sets the parent in the Metadata
	 * component of this GameObject and adds this GameObject to the children list of the parent
	 * GameObject.
	 * 
	 * \param parent The parent GameObject
	 */
	void set_parent(const GameObject & parent);
	/**
	 * \brief Add a component to the GameObject
	 * 
	 * This method adds a component to the GameObject. It forwards the arguments to the
	 * ComponentManager.
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
};

} // namespace crepe

#include "GameObject.hpp"
