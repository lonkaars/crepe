#include "EventManager.h"

using namespace crepe;

EventManager & EventManager::get_instance() {
	static EventManager instance;
	return instance;
}

void EventManager::dispatch_events() {
	for (auto event_it = this->events_queue.begin(); event_it != this->events_queue.end();) {
		std::unique_ptr<Event> & event = (*event_it).event;
		int channel = (*event_it).channel;
		std::type_index event_type = (*event_it).type;

		bool event_handled = false;
		auto handlers_it = this->subscribers.find(event_type);
		if (handlers_it == this->subscribers.end()) {
			continue;
		}
		std::vector<CallbackEntry> & handlers = handlers_it->second;

		for (auto handler_it = handlers.begin(); handler_it != handlers.end();
				++handler_it) {
			// If callback is executed and returns true, remove the event from the queue
			if ((*handler_it).callback->exec(*event)) {
				event_it = this->events_queue.erase(event_it);
				event_handled = true;
				break;
			}
		}

		if (!event_handled) {
			++event_it;
		}
	}
}

void EventManager::clear() {
	this->subscribers.clear();
	this->events_queue.clear();
}

void EventManager::unsubscribe(subscription_t event_id) {
    for (auto& [event_type, handlers] : this->subscribers) {
        for (auto it = handlers.begin(); it != handlers.end();) {
            if (it->id == event_id) {
                it = handlers.erase(it);
                return;
            } else {
                ++it;
            }
        }
    }
}

