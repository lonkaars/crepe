#pragma once

#include <functional>

#include "Event.h"
#include "UIObject.h"

namespace crepe {

/**
 * \brief Button component.
 * 
 * This component creates a clickable surface at the transform location with the specified width and height.
 * 
 * The Button can be used in scripts by subscribing a EventHandler to the following events:
 * - **ButtonPressEvent**: Triggered when the surface is clicked with the mouse. Contains GameObject metadata.
 * - **MouseEnterEvent**: Triggered when the mouse enters the button area. Contains GameObject metadata.
 * - **MouseExitEvent**: Triggered when the mouse leaves the button area. Contains GameObject metadata.
 * \see EventManager
 * 
 */
class Button : public UIObject {
public:
	/**
	 * \brief Constructs a Button with the specified game object ID and dimensions.
	 *
	 * \param id The unique ID of the game object associated with this button.
	 * \param dimensions The width and height of the UIObject
	 * \param offset The offset relative this GameObjects Transform
	 */
	Button(game_object_id_t id, const vec2 & dimensions, const vec2 & offset);

private:
	//! friend relation hover variable
	friend class InputSystem;
	//! Indicates whether the mouse is currently hovering over the button
	bool hover = false;
};

} // namespace crepe
