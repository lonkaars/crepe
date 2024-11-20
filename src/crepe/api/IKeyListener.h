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
	IKeyListener(int channel = EventManager::CHANNEL_ALL);
	virtual ~IKeyListener();
	IKeyListener(const IKeyListener &) = delete;
	IKeyListener & operator=(const IKeyListener &) = delete;
	IKeyListener & operator=(IKeyListener &&) = delete;
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
private:
	//! Key press event id
	subscription_t press_id = -1;
	//!< Key release event id
	subscription_t release_id = -1;
	EventManager & event_manager;
};

} // namespace crepe
