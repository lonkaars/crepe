#pragma once

#include "Event.h"
#include "EventHandler.h"
#include "EventManager.h"

namespace crepe {

/**
 * \class IMouseListener
 * \brief Interface for mouse event handling in the application.
 */
class IMouseListener {
public:
	/**
     * \brief Constructs an IMouseListener with a specified channel.
     * \param channel The channel ID for event handling.
     */
	IMouseListener(int channel = CHANNEL_ALL);
	virtual ~IMouseListener();
	IMouseListener & operator=(const IMouseListener &) = delete;
	IMouseListener(const IMouseListener &) = delete;
	IMouseListener & operator=(const IMouseListener &&) = delete;
	IMouseListener(IMouseListener &&) = delete;

	/**
     * \brief Move assignment operator (deleted).
     */
	IMouseListener & operator=(IMouseListener &&) = delete;

	/**
     * \brief Handles a mouse click event.
     * \param event The mouse click event to handle.
     * \return True if the event was handled, false otherwise.
     */
	virtual bool on_mouse_clicked(const MouseClickEvent & event) = 0;

	/**
     * \brief Handles a mouse press event.
     * \param event The mouse press event to handle.
     * \return True if the event was handled, false otherwise.
     */
	virtual bool on_mouse_pressed(const MousePressEvent & event) = 0;

	/**
     * \brief Handles a mouse release event.
     * \param event The mouse release event to handle.
     * \return True if the event was handled, false otherwise.
     */
	virtual bool on_mouse_released(const MouseReleaseEvent & event) = 0;

	/**
     * \brief Handles a mouse move event.
     * \param event The mouse move event to handle.
     * \return True if the event was handled, false otherwise.
     */
	virtual bool on_mouse_moved(const MouseMoveEvent & event) = 0;

protected:
	/**
     * \brief Subscribes to mouse events on the specified channel.
     */
	void subscribe_events();

	/**
     * \brief Unsubscribes from mouse events on the specified channel.
     */
	void unsubscribe_events();

private:
	//! Indicates whether mouse listening is active.
	bool active = true;
	//! Channel ID for event handling.
	int channel = 0;
	//! Mouse click event handler.
	EventHandler<MouseClickEvent> mouse_click_handler;
	//! Mouse press event handler.
	EventHandler<MousePressEvent> mouse_press_handler;
	//! Mouse release event handler.
	EventHandler<MouseReleaseEvent> mouse_release_handler;
	//! Mouse move event handler.
	EventHandler<MouseMoveEvent> mouse_move_handler;
	EventManager & event_manager;
};

} //namespace crepe
