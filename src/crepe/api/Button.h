#pragma once

#include <functional>

#include "UiObject.h"

namespace crepe {

/**
 * \class Button
 * \brief Represents a clickable UI button, derived from the UiObject class.
 */
class Button : public UiObject {
public:
    /**
     * \brief Constructs a Button with the specified game object ID.
     * \param id The unique ID of the game object associated with this button.
     */
    Button(game_object_id_t id);

    //! Indicates if the button is interactable (can be clicked).
    bool interactable = true;

    //! Indicates if the button is a toggle button (can be pressed and released).
    bool is_toggle = false;

    //! Indicates whether the button is currently pressed.
    bool is_pressed = false;

    //! Indicates whether the mouse is currently hovering over the button.
    bool hover = false;

    //! The callback function to be executed when the button is clicked.
    std::function<void()> on_click;

public:
    /**
     * \brief Retrieves the maximum number of instances allowed for this button type.
     * \return Always returns 1, as only a single instance is allowed.
     */
    virtual int get_instances_max() const override { return 1; }
};

} // namespace crepe
