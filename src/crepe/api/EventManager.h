#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Event.h"
#include "EventHandler.h"

namespace crepe {

//! Event listener unique ID
typedef size_t subscription_t;

/**
 * \brief Event channel
 *
 * Events can be sent to a specific channel, which prevents listeners on other channels from
 * being called. The default channel is EventManager::CHANNEL_ALL, which calls all listeners.
 */
typedef size_t event_channel_t;

/**
 * \class EventManager
 * \brief Manages event subscriptions, triggers, and queues, enabling decoupled event handling.
 * 
 * The `EventManager` acts as a centralized event system. It allows for registering callbacks
 * for specific event types, triggering events synchronously, queueing events for later
 * processing, and managing subscriptions via unique identifiers.
 */
class EventManager {
public:
	static constexpr const event_channel_t CHANNEL_ALL = -1;

	/**
	 * \brief Get the singleton instance of the EventManager.
	 * 
	 * This method returns the unique instance of the EventManager, creating it if it
	 * doesn't already exist. Ensures only one instance is active in the program.
	 * 
	 * \return Reference to the singleton instance of the EventManager.
	 */
	static EventManager & get_instance();

	/**
	 * \brief Subscribe to a specific event type.
	 * 
	 * Registers a callback for a given event type and optional channel. Each callback
	 * is assigned a unique subscription ID that can be used for later unsubscription.
	 * 
	 * \tparam EventType The type of the event to subscribe to.
	 * \param callback The callback function to be invoked when the event is triggered.
	 * \param channel The channel number to subscribe to (default is CHANNEL_ALL, which listens to all channels).
	 * \return A unique subscription ID associated with the registered callback.
	 */
	template <typename EventType>
	subscription_t subscribe(const EventHandler<EventType> & callback,
							 event_channel_t channel = CHANNEL_ALL);

	/**
	 * \brief Unsubscribe a previously registered callback.
	 * 
	 * Removes a callback from the subscription list based on its unique subscription ID.
	 * 
	 * \param event_id The unique subscription ID of the callback to remove.
	 */
	void unsubscribe(subscription_t event_id);

	/**
	 * \brief Trigger an event immediately.
	 * 
	 * Synchronously invokes all registered callbacks for the given event type on the specified channel.
	 * 
	 * \tparam EventType The type of the event to trigger.
	 * \param event The event instance to pass to the callbacks.
	 * \param channel The channel to trigger the event on (default is CHANNEL_ALL, which triggers on all channels).
	 */
	template <typename EventType>
	void trigger_event(const EventType & event = {}, event_channel_t channel = CHANNEL_ALL);

	/**
	 * \brief Queue an event for later processing.
	 * 
	 * Adds an event to the event queue to be processed during the next call to `dispatch_events`.
	 * 
	 * \tparam EventType The type of the event to queue.
	 * \param event The event instance to queue.
	 * \param channel The channel to associate with the event (default is CHANNEL_ALL).
	 */
	template <typename EventType>
	void queue_event(const EventType & event = {}, event_channel_t channel = CHANNEL_ALL);

	/**
	 * \brief Process all queued events.
	 * 
	 * Iterates through the event queue and triggers callbacks for each queued event.
	 * Events are removed from the queue once processed.
	 */
	void dispatch_events();

	/**
	 * \brief Clear all subscriptions.
	 * 
	 * Removes all registered event handlers and clears the subscription list.
	 */
	void clear();

private:
	/**
	 * \brief Default constructor for the EventManager.
	 * 
	 * Constructor is private to enforce the singleton pattern.
	 */
	EventManager() = default;

	/**
	 * \struct QueueEntry
	 * \brief Represents an entry in the event queue.
	 */
	struct QueueEntry {
		std::unique_ptr<Event> event; ///< The event instance.
		event_channel_t channel = CHANNEL_ALL; ///< The channel associated with the event.
		std::type_index type; ///< The type of the event.
	};

	/**
	 * \brief Internal event handler
	 *
	 * This function processes a single event, and is used to process events both during
	 * EventManager::dispatch_events and inside EventManager::trigger_event
	 *
	 * \param type \c typeid of concrete Event class
	 * \param channel Event channel
	 * \param data Event data
	 */
	void handle_event(std::type_index type, event_channel_t channel, const Event & data);

	/**
	 * \struct CallbackEntry
	 * \brief Represents a registered event handler callback.
	 */
	struct CallbackEntry {
		std::unique_ptr<IEventHandlerWrapper> callback; ///< The callback function wrapper.
		event_channel_t channel = CHANNEL_ALL; ///< The channel this callback listens to.
		subscription_t id = -1; ///< Unique subscription ID.
	};

	//! The queue of events to be processed during dispatch.
	std::vector<QueueEntry> events_queue;

	//! A map of event type to registered callbacks.
	std::unordered_map<std::type_index, std::vector<CallbackEntry>> subscribers;

	//! Counter to generate unique subscription IDs.
	subscription_t subscription_counter = 0;
};

} // namespace crepe

#include "EventManager.hpp"
