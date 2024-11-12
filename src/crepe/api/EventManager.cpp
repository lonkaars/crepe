#include "EventManager.h"



void EventManager::dispatch_events() {
    for (auto event_it = events_queue.begin(); event_it != events_queue.end();) {
        auto& event = std::get<0>(*event_it);
        int channel = std::get<1>(*event_it); 
        std::type_index event_type = std::get<2>(*event_it); 
        if (channel) {
            auto handlers_it = subscribers_by_event_id.find(event_type);
            if (handlers_it != subscribers_by_event_id.end()) {
                auto& handlers_map = handlers_it->second;
                auto handlers = handlers_map.find(channel);
                if (handlers != handlers_map.end()) {
                    auto& callbacks = handlers->second;
                    for (auto& handler : callbacks) {
                        handler->exec(*event);
                    }
                }
            }
        } else {
            auto handlers_it = subscribers.find(event_type);
            if (handlers_it != subscribers.end()) {
                auto& handlers = handlers_it->second;
                for (auto& handler : handlers) {
                    handler->exec(*event);
                }
            }
        }

        if (event->handled) {
            event_it = events_queue.erase(event_it);
        } else {
            ++event_it;
        }
    }
}

