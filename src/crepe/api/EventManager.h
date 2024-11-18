#pragma once

#include <functional>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Event.h"
#include "EventHandler.h"

namespace crepe {

/**
 * \class EventManager
 * \brief The EventManager class is responsible for managing the subscription, triggering, 
 * and queueing of events. It handles events and dispatches them to appropriate subscribers.
 */
class EventManager {
public:
	/**
     * \brief Get the singleton instance of the EventManager.
     * 
     * This method returns the unique instance of the EventManager, creating it on the first call.
     * 
     * \return Reference to the EventManager instance.
     */
	static EventManager & get_instance();

	/**
     * \brief Subscribe to an event.
     * 
     * This method allows the registration of a callback for a specific event type and channel.
     * 
     * \tparam EventType The type of the event to subscribe to.
     * \param callback The callback function to invoke when the event is triggered.
     * \param channel The channel number to subscribe to (default is 0).
     */
	template <typename EventType>
	void subscribe(EventHandler<EventType> && callback, int channel = 0);

	/**
     * \brief Unsubscribe from an event.
     * 
     * This method removes a previously registered callback from an event.
     * 
     * \tparam EventType The type of the event to unsubscribe from.
     * \param callback The callback function to remove from the subscription list.
     * \param channel The event ID to unsubscribe from.
     */
	template <typename EventType>
	void unsubscribe(const EventHandler<EventType> &, int channel = 0);

	/**
     * \brief Trigger an event.
     * 
     * This method invokes the appropriate callback(s) for the specified event.
     * 
     * \tparam EventType The type of the event to trigger.
     * \param event The event data to pass to the callback.
     * \param channel The channel from which to trigger the event (default is 0).
     */
	template <typename EventType>
	void trigger_event(const EventType & event, int channel = 0);

	/**
     * \brief Queue an event for later processing.
     * 
     * This method adds an event to the event queue, which will be processed in the 
     * dispatch_events function.
     * 
     * \tparam EventType The type of the event to queue.
     * \param event The event to queue.
     * \param channel The channel number for the event (default is 0).
     */
	template <typename EventType>
	void queue_event(EventType && event, int channel = 0);

	/**
     * \brief Dispatch all queued events.
     * 
     * This method processes all events in the event queue and triggers the corresponding 
     * callbacks for each event.
     */
	void dispatch_events();

private:
	/**
     * \brief Default constructor for the EventManager.
     * 
     * This constructor is private to enforce the singleton pattern.
     */
	EventManager() = default;

	//! The queue of events to be processed.
	std::vector<std::tuple<std::unique_ptr<Event>, int, std::type_index>> events_queue;
	//! Registered event handlers.
	std::unordered_map<std::type_index, std::vector<std::unique_ptr<IEventHandlerWrapper>>>
		subscribers;
	//! Event handlers indexed by event ID.
	std::unordered_map<
		std::type_index,
		std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>>
		subscribers_by_event_id;
};

} // namespace crepe
#include "EventManager.hpp"
