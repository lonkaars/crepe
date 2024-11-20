#include "EventManager.h"

using namespace crepe;

EventManager & EventManager::get_instance() {
	static EventManager instance;
	return instance;
}

void EventManager::dispatch_events() {
	using HandlersMap
		= std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>;
	using HandlersVec = std::vector<std::unique_ptr<IEventHandlerWrapper>>;

	for (auto event_it = this->events_queue.begin(); event_it != this->events_queue.end();) {
		std::unique_ptr<Event> & event = (*event_it).event;
		int channel = (*event_it).channel;
		std::type_index event_type = (*event_it).type;

		bool event_handled = false;

		if (channel) {
			auto handlers_it = subscribers_by_event_id.find(event_type);
			if (handlers_it != subscribers_by_event_id.end()) {
				HandlersMap & handlers_map = handlers_it->second;
				auto handlers = handlers_map.find(channel);
				if (handlers != handlers_map.end()) {
					HandlersVec & callbacks = handlers->second;
					for (auto handler_it = callbacks.begin(); handler_it != callbacks.end();
						 ++handler_it) {
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
			auto handlers_it = this->subscribers.find(event_type);
			if (handlers_it != this->subscribers.end()) {
				HandlersVec & handlers = handlers_it->second;
				for (auto handler_it = handlers.begin(); handler_it != handlers.end();
					 ++handler_it) {
					// remove event from queue since and continue when callback returns true
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
void EventManager::clear(){
	this->subscribers.clear();
	this->events_queue.clear();
	this->subscribers_by_event_id.clear();
}
