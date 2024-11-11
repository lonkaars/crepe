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

class EventManager {
public:
	EventManager(const EventManager &) = delete;
	const EventManager & operator=(const EventManager &) = delete;
	static EventManager & get_instance() {
		static EventManager instance;
		return instance;
	}
	template <typename EventType>
	void subscribe(EventHandler<EventType> && callback, int channel = 0);
	template <typename EventType>
	void unsubscribe(const EventHandler<EventType> &, int eventId);
	template <typename EventType>
	void trigger_event(const EventType & event, int channel);
	void queue_event(std::unique_ptr<Event> && event, int channel);
	void dispatch_events();

private:
	EventManager() = default;
	std::vector<std::pair<std::unique_ptr<Event>, int>> events_queue;
	std::unordered_map<std::type_index, std::vector<std::unique_ptr<IEventHandlerWrapper>>> subscribers;
	std::unordered_map<std::type_index, std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>> subscribers_by_event_id;
};

template <typename EventType>
void EventManager::subscribe(EventHandler<EventType> && callback, int channel){
    std::type_index event_type = typeid(EventType);
    auto handler = std::make_unique<EventHandlerWrapper<EventType>>(callback);
    
    if (channel) {
        auto & handlers_map = subscribers_by_event_id[event_type];
        auto handlers = handlers_map.find(channel);
        if (handlers != handlers_map.end()) {
            handlers->second.emplace_back(std::move(handler));
        } else {
            handlers_map[channel].emplace_back(std::move(handler));
        }
    } else {
        subscribers[event_type].emplace_back(std::move(handler));
    }
}

template <typename EventType>
void EventManager::trigger_event(const EventType & event, int eventId) {
    std::type_index event_type = std::type_index(typeid(EventType));
    
    if (eventId > 0) {
        auto handlers_it = subscribers_by_event_id[event_type].find(eventId);
        if (handlers_it != subscribers_by_event_id[event_type].end()) {
            auto & callbacks = handlers_it->second;
            for (auto it = callbacks.begin(); it != callbacks.end();) {
                if ((*it)->exec(event)) {
                    it = callbacks.erase(it);
                } else {
                    ++it;
                }
            }
        }
    } else {
        auto & handlers = subscribers[event_type];
        for (auto & handler : handlers) {
            handler->exec(event);
        }
    }
}
template <typename EventType>
void EventManager::unsubscribe(const EventHandler<EventType> & callback, int channel) {
    std::type_index event_type(typeid(EventType));
    const std::string handler_name = callback.target_type().name();
	std::cout << "unsubcribe name: " << handler_name << std::endl;

    if (channel) {
        auto subscriber_list = subscribers_by_event_id.find(event_type);
        if (subscriber_list != subscribers_by_event_id.end()) {
            auto& handlers_map = subscriber_list->second;
            auto handlers = handlers_map.find(channel);
            if (handlers != handlers_map.end()) {
                auto& callbacks = handlers->second;
                for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
                    if ((*it)->get_type() == handler_name) {
						std::cout << "successfully erased an event" << std::endl;
                        it = callbacks.erase(it);
                        return;
                    }
                }
            }
        }
    } else {
        auto handlers_it = subscribers.find(event_type);
        if (handlers_it != subscribers.end()) {
            auto& handlers = handlers_it->second;
            for (auto it = handlers.begin(); it != handlers.end(); ++it) {
                if ((*it)->get_type() == handler_name) {
					std::cout << "successfully erased an event" << std::endl;
                    it = handlers.erase(it);
                    return;
                }
            }
        }
    }
}
