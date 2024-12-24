#pragma once

#include "../types.h"

#include "UIObject.h"

namespace crepe {

/**
 * \brief Button component.
 * 
 * This component creates a clickable surface at the transform location with the specified width and height.
 * 
 * The Button can be used in scripts by subscribing a EventHandler to the following events:
 * - ButtonPressEvent
 * - ButtonEnterEvent
 * - ButtonExitEvent
 * \see EventManager
 * 
 */
class Button : public UIObject {
public:
	struct Data {
		//! variable indicating if transform is relative to camera(false) or world(true)
		bool world_space = false;
	};

public:
	/**
	 * \brief Constructs a Button with the specified game object ID and dimensions.
	 *
	 * \param id The unique ID of the game object associated with this button.
	 * \param dimensions The width and height of the UIObject
	 * \param offset The offset relative this GameObjects Transform
	 * \param data additional data the button has
	 */
	Button(
		game_object_id_t id, const vec2 & dimensions, const Data & data,
		const vec2 & offset = {0, 0}
	);
	/**
	 * \brief Get the maximum number of instances for this component
	 *
	 * Since the button Event transfers the GameObject Metadata it will be the same for each button so only one button is allowed per GameObject	
	 * 
	 * \return 1
	 */
	virtual int get_instances_max() const { return 1; }

public:
	Data data;

private:
	//! friend relation hover variable
	friend class InputSystem;
	//! Indicates whether the mouse is currently hovering over the button
	bool hover = false;
};

} // namespace crepe
