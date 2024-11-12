#include "EventManager.h"



void EventManager::dispatch_events() {
    for (auto event_it = events_queue.begin(); event_it != events_queue.end();) {
        auto& event = std::get<0>(*event_it);
        int channel = std::get<1>(*event_it); 
        std::type_index event_type = std::get<2>(*event_it); 

        bool event_handled = false;

        if (channel) {
            auto handlers_it = subscribers_by_event_id.find(event_type);
            if (handlers_it != subscribers_by_event_id.end()) {
                auto& handlers_map = handlers_it->second;
                auto handlers = handlers_map.find(channel);
                if (handlers != handlers_map.end()) {
                    auto& callbacks = handlers->second;
                    for (auto& handler : callbacks) {
                        if (handler->exec(*event)) {
                            event_it = events_queue.erase(event_it);
                            event_handled = true;
                            break;
                        }
                    }
                }
            }
        } else {
            // Handle event for all channels
            auto handlers_it = subscribers.find(event_type);
            if (handlers_it != subscribers.end()) {
                auto& handlers = handlers_it->second;
                for (auto& handler : handlers) {
                    if (handler->exec(*event)) {
                        event_it = events_queue.erase(event_it);
                        event_handled = true;
                        break;
                    }
                }
            }
        }

        if (!event_handled) {
            ++event_it;
        }
    }
}


