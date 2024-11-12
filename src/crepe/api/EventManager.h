#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>
#include <iostream>
#include <typeindex>
#include <type_traits>
#include "Event.h"
#include "EventHandler.h"
//#include "keyCodes.h"

/**
 * @class EventManager
 * @brief The EventManager class is responsible for managing the subscription, triggering, 
 * and queueing of events. It handles events and dispatches them to appropriate subscribers.
 */
class EventManager {
public:
    /**
     * \brief Deleted copy constructor to prevent copying of the EventManager instance.
     */
    EventManager(const EventManager &) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent assignment of the EventManager instance.
     */
    const EventManager & operator=(const EventManager &) = delete;

    /**
     * @brief Get the singleton instance of the EventManager.
     * 
     * This method returns the unique instance of the EventManager, creating it on the first call.
     * 
     * @return Reference to the EventManager instance.
     */
    static EventManager & get_instance() {
        static EventManager instance;
        return instance;
    }

    /**
     * @brief Subscribe to an event.
     * 
     * This method allows the registration of a callback for a specific event type and channel.
     * 
     * @tparam EventType The type of the event to subscribe to.
     * @param callback The callback function to invoke when the event is triggered.
     * @param channel The channel number to subscribe to (default is 0).
     */
    template <typename EventType>
    void subscribe(EventHandler<EventType> && callback, int channel = 0);

    /**
     * @brief Unsubscribe from an event.
     * 
     * This method removes a previously registered callback from an event.
     * 
     * @tparam EventType The type of the event to unsubscribe from.
     * @param callback The callback function to remove from the subscription list.
     * @param eventId The event ID to unsubscribe from.
     */
    template <typename EventType>
    void unsubscribe(const EventHandler<EventType> &, int eventId);

    /**
     * @brief Trigger an event.
     * 
     * This method invokes the appropriate callback(s) for the specified event.
     * 
     * @tparam EventType The type of the event to trigger.
     * @param event The event data to pass to the callback.
     * @param channel The channel from which to trigger the event (default is 0).
     */
    template <typename EventType>
    void trigger_event(const EventType & event, int channel);

    /**
     * @brief Queue an event for later processing.
     * 
     * This method adds an event to the event queue, which will be processed in the 
     * dispatch_events function.
     * 
     * @tparam EventType The type of the event to queue.
     * @param event The event to queue.
     * @param channel The channel number for the event (default is 0).
     */
    template <typename EventType>
    void queue_event(EventType&& event, int channel);

    /**
     * @brief Dispatch all queued events.
     * 
     * This method processes all events in the event queue and triggers the corresponding 
     * callbacks for each event.
     */
    void dispatch_events();

private:
    /**
     * @brief Default constructor for the EventManager.
     * 
     * This constructor is private to enforce the singleton pattern.
     */
    EventManager() = default;

    //! The queue of events to be processed.
    std::vector<std::tuple<std::unique_ptr<Event>, int, std::type_index>> events_queue; 
	//! Registered event handlers.
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<IEventHandlerWrapper>>> subscribers; 
	//! Event handlers indexed by event ID.
    std::unordered_map<std::type_index, std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>> subscribers_by_event_id; 
};

template <typename EventType>
void EventManager::subscribe(EventHandler<EventType> && callback, int channel) {
    std::type_index event_type = typeid(EventType);
    std::unique_ptr<EventHandlerWrapper<EventType>> handler = std::make_unique<EventHandlerWrapper<EventType>>(callback);
    
    if (channel) {
        std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>& handlers_map = subscribers_by_event_id[event_type];
        std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlers = handlers_map.find(channel);
        if (handlers != handlers_map.end()) {
            handlers->second.emplace_back(std::move(handler));
        } else {
            handlers_map[channel].emplace_back(std::move(handler));
        }
    } else {
        std::vector<std::unique_ptr<IEventHandlerWrapper>>& handlers = subscribers[event_type];
        handlers.emplace_back(std::move(handler));
    }
}

template <typename EventType>
void EventManager::queue_event(EventType&& event, int channel) {
    std::type_index event_type = std::type_index(typeid(EventType));
    
    std::unique_ptr<EventType> event_ptr = std::make_unique<EventType>(std::forward<EventType>(event));

    std::tuple<std::unique_ptr<Event>, int, std::type_index> tuple(
        std::move(event_ptr),
        channel,
        event_type
    );
    events_queue.push_back(std::move(tuple));
}

template <typename EventType>
void EventManager::trigger_event(const EventType & event, int eventId) {
    std::type_index event_type = std::type_index(typeid(EventType));
    
    if (eventId > 0) {
        std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>& handlers_map = subscribers_by_event_id[event_type];
        std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlers_it = handlers_map.find(eventId);
        
        if (handlers_it != handlers_map.end()) {
            std::vector<std::unique_ptr<IEventHandlerWrapper>>& callbacks = handlers_it->second;
            for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it = callbacks.begin(); it != callbacks.end();) {
                if ((*it)->exec(event)) {
                    it = callbacks.erase(it);
                } else {
                    ++it;
                }
            }
        }
    } else {
        std::vector<std::unique_ptr<IEventHandlerWrapper>>& handlers = subscribers[event_type];
        for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it = handlers.begin(); it != handlers.end(); ++it) {
            (*it)->exec(event);
        }
    }
}

template <typename EventType>
void EventManager::unsubscribe(const EventHandler<EventType> & callback, int channel) {
    std::type_index event_type(typeid(EventType));
    std::string handler_name = callback.target_type().name();

    if (channel) {
        std::unordered_map<std::type_index, std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>>::iterator subscriber_list = subscribers_by_event_id.find(event_type);
        if (subscriber_list != subscribers_by_event_id.end()) {
            std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>& handlers_map = subscriber_list->second;
            std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlers = handlers_map.find(channel);
            if (handlers != handlers_map.end()) {
                std::vector<std::unique_ptr<IEventHandlerWrapper>>& callbacks = handlers->second;
                for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it = callbacks.begin(); it != callbacks.end(); ++it) {
                    if ((*it)->get_type() == handler_name) {
                        it = callbacks.erase(it);
                        return;
                    }
                }
            }
        }
    } else {
        std::unordered_map<std::type_index, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlers_it = subscribers.find(event_type);
        if (handlers_it != subscribers.end()) {
            std::vector<std::unique_ptr<IEventHandlerWrapper>>& handlers = handlers_it->second;
            for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it = handlers.begin(); it != handlers.end(); ++it) {
                if ((*it)->get_type() == handler_name) {
                    it = handlers.erase(it);
                    return;
                }
            }
        }
    }
}
