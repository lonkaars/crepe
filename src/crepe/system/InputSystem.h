#pragma once

#include "facade/SDLContext.h"
#include "types.h"
#include "util/OptionalRef.h"

#include "System.h"

namespace crepe {

class Camera;
class Button;
class Transform;

/**
 * \brief Handles the processing of input events like mouse and keyboard interactions.
 *
 * This system processes events such as mouse clicks, mouse movement, and keyboard
 * actions. It is responsible for detecting interactions with UI buttons and
 * passing the corresponding events to the registered listeners.
 */
class InputSystem : public System {
public:
    using System::System;

    /**
     * \brief Updates the system, processing all input events.
     * This method processes all events and triggers corresponding actions.
     */
    void update() override;

private:
    	//! Reference to the currently active camera.
    	OptionalRef<Camera> curr_cam_ref;

    	//! Stores the last position of the mouse when the button was pressed.
    	std::pair<int, int> last_mouse_down_position{INFINITY, INFINITY};

    	//! Stores the last mouse button pressed.
    	MouseButton last_mouse_button = MouseButton::NONE;
	//
    	//! The tolerance in game units for detecting a mouse click.
    	const int click_tolerance = 5;

	/**
	* \brief Handles the mouse click event.
	* \param mouse_button The mouse button involved in the click.
	* \param world_mouse_x The X coordinate of the mouse in world space.
	* \param world_mouse_y The Y coordinate of the mouse in world space.
	*
	* This method processes the mouse click event and triggers the corresponding button action.
	*/
	void handle_click(const MouseButton& mouse_button, const int& world_mouse_x, const int& world_mouse_y);

	/**
	* \brief Handles the mouse movement event.
	* \param event_data The event data containing information about the mouse movement.
	* \param world_mouse_x The X coordinate of the mouse in world space.
	* \param world_mouse_y The Y coordinate of the mouse in world space.
	*
	* This method processes the mouse movement event and updates the button hover state.
	*/
	void handle_move(const SDLContext::EventData& event_data, const int& world_mouse_x, const int& world_mouse_y);

	/**
	* \brief Checks if the mouse position is inside the bounds of the button.
	* \param mouse_x The X coordinate of the mouse.
	* \param mouse_y The Y coordinate of the mouse.
	* \param button The button to check.
	* \param transform The transform component of the button.
	* \return True if the mouse is inside the button, false otherwise.
	*/
	bool is_mouse_inside_button(const int& mouse_x, const int& mouse_y, const Button& button, const Transform& transform);

	/**
	* \brief Handles the button press event, calling the on_click callback if necessary.
	* \param button The button being pressed.
	*
	* This method triggers the on_click action for the button when it is pressed.
	*/
	void handle_button_press(Button& button);
};

} // namespace crepe
