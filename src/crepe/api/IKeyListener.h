#pragma once

#include "Event.h"
#include "EventHandler.h"
#include "EventManager.h"

namespace crepe {

/**
 * \class IKeyListener
 * \brief Interface for keyboard event handling in the application.
 */
class IKeyListener {
public:
	/**
     * \brief Constructs an IKeyListener with a specified channel.
     * \param channel The channel ID for event handling.
     */
	IKeyListener(int channel);
	IKeyListener();
	virtual ~IKeyListener();
	IKeyListener(const IKeyListener &) = delete;
	IKeyListener & operator=(const IKeyListener &) = delete;
	IKeyListener(IKeyListener &&) = delete;

	/**
     * \brief Pure virtual function to handle key press events.
     * \param event The key press event to handle.
     * \return True if the event was handled, false otherwise.
     */
	virtual bool on_key_pressed(const KeyPressEvent & event) = 0;

	/**
     * \brief Pure virtual function to handle key release events.
     * \param event The key release event to handle.
     * \return True if the event was handled, false otherwise.
     */
	virtual bool on_key_released(const KeyReleaseEvent & event) = 0;

	/**
     * \brief Activates key listening.
     */
	void activate_keys();

	/**
     * \brief Deactivates key listening.
     */
	void deactivate_keys();

	/**
     * \brief Sets the channel ID for event handling.
     * \param channel The channel ID to set.
     */
	void set_channel(int channel);

protected:
	/**
     * \brief Subscribes to key events.
     */
	void subscribe_events();

	/**
     * \brief Unsubscribes from key events.
     */
	void unsubscribe_events();

private:
	//! Indicates whether key listening is active.
	bool active = true;
	//! Channel ID for event handling.
	int channel = 0;
	//! Key press event handler.
	EventHandler<KeyPressEvent> key_pressed_handler;
	//!< Key release event handler.
	EventHandler<KeyReleaseEvent> key_released_handler;
	EventManager & event_manager;
};

} // namespace crepe
