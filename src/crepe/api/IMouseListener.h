#pragma once

#include "../manager/EventManager.h"

#include "Event.h"
#include "EventHandler.h"

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
	IMouseListener(event_channel_t channel = EventManager::CHANNEL_ALL);
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

private:
	//! Mouse click event id
	subscription_t click_id = -1;
	//! Mouse press event id
	subscription_t press_id = -1;
	//! Mouse release event id
	subscription_t release_id = -1;
	//! Mouse move event id
	subscription_t move_id = -1;
	//! EventManager reference
	EventManager & event_manager;
};

} //namespace crepe
