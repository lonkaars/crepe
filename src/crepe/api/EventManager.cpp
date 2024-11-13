#include "EventManager.h"

EventManager & EventManager::get_instance() {
	static EventManager instance;
	return instance;
}

void EventManager::dispatch_events() {
    for (std::vector<std::tuple<std::unique_ptr<Event>, int, std::type_index>>::iterator event_it = this->events_queue.begin(); event_it != this->events_queue.end();) {
        std::unique_ptr<Event>& event = std::get<0>(*event_it);
        int channel = std::get<1>(*event_it);
        std::type_index event_type = std::get<2>(*event_it);

        bool event_handled = false;

        if (channel) {
            std::unordered_map<std::type_index, std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>>::iterator handlers_it = subscribers_by_event_id.find(event_type);
            if (handlers_it != subscribers_by_event_id.end()) {
                std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>& handlers_map = handlers_it->second;
                std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlers = handlers_map.find(channel);
                if (handlers != handlers_map.end()) {
                    std::vector<std::unique_ptr<IEventHandlerWrapper>>& callbacks = handlers->second;
                    for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator handler_it = callbacks.begin(); handler_it != callbacks.end(); ++handler_it) {
                        if ((*handler_it)->exec(*event)) {
                            event_it = events_queue.erase(event_it);
                            event_handled = true;
                            break;
                        }
                    }
                }
            }
        } else {
            // Handle event for all channels
            std::unordered_map<std::type_index, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlers_it = this->subscribers.find(event_type);
            if (handlers_it != this->subscribers.end()) {
                std::vector<std::unique_ptr<IEventHandlerWrapper>>& handlers = handlers_it->second;
                for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator handler_it = handlers.begin(); handler_it != handlers.end(); ++handler_it) {
                    if ((*handler_it)->exec(*event)) {
                        event_it = this->events_queue.erase(event_it);
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
