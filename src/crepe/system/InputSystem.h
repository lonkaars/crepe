#pragma once

#include "facade/SDLContext.h"
#include "util/OptionalRef.h"

#include "System.h"

namespace crepe {

class Button;

class Transform;
/**
 * \class InputSystem
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
	//! Stores the last position of the mouse when the button was pressed.
	std::pair<int, int> last_mouse_down_position{-1, -1};

	//! Stores the last mouse button pressed.
	MouseButton last_mouse_button = MouseButton::NONE;

	//! The tolerance in pixels for detecting a mouse click.
	const int click_tolerance = 5;

	/**
     * \brief Handles the click event.
     * \param eventData The event data containing information about the mouse click.
     * 
     * This method processes the mouse click event and triggers the corresponding button action.
     */
	void handle_click(const SDLContext::EventData & eventData);

	/**
     * \brief Handles the mouse movement event.
     * \param eventData The event data containing information about the mouse movement.
     * 
     * This method processes the mouse movement event and updates the button hover state.
     */
	void handle_move(const SDLContext::EventData & eventData);

	/**
     * \brief Finds the transform component associated with a button.
     * \param button The button to find the associated transform for.
     * \param transforms A list of transforms to search through.
     * \return A pointer to the transform of the button, or nullptr if not found.
     */
	OptionalRef<Transform>
	find_transform_for_button(Button & button,
							  std::vector<std::reference_wrapper<Transform>> & transforms);

	/**
     * \brief Checks if the mouse position is inside the bounds of the button.
     * \param eventData The event data containing the mouse position.
     * \param button The button to check.
     * \param transform The transform component of the button.
     * \return True if the mouse is inside the button, false otherwise.
     */
	bool is_mouse_inside_button(const SDLContext::EventData & eventData, const Button & button,
								const Transform & transform);

	/**
     * \brief Handles the button press event, calling the on_click callback if necessary.
     * \param button The button being pressed.
     * 
     * This method triggers the on_click action for the button when it is pressed.
     */
	void handle_button_press(Button & button);
};

} // namespace crepe
