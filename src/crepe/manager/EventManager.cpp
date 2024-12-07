#include "EventManager.h"

using namespace crepe;
using namespace std;

EventManager::EventManager(Mediator & mediator) : Manager(mediator){
	this->mediator.event_manager = *this;
}
void EventManager::dispatch_events() {
	for (auto & event : this->events_queue) {
		this->handle_event(event.type, event.channel, *event.event.get());
	}
	this->events_queue.clear();
}

void EventManager::handle_event(type_index type, event_channel_t channel, const Event & data) {
	auto handlers_it = this->subscribers.find(type);
	if (handlers_it == this->subscribers.end()) return;

	vector<CallbackEntry> & handlers = handlers_it->second;
	for (auto & handler : handlers) {
		bool check_channel = handler.channel != CHANNEL_ALL || channel != CHANNEL_ALL;
		if (check_channel && handler.channel != channel) continue;

		bool handled = handler.callback->exec(data);
		if (handled) return;
	}
}

void EventManager::clear() {
	this->subscribers.clear();
	this->events_queue.clear();
}

void EventManager::unsubscribe(subscription_t id) {
	for (auto & [event_type, handlers] : this->subscribers) {
		for (auto it = handlers.begin(); it != handlers.end(); it++) {
			// find listener with subscription id
			if ((*it).id != id) continue;
			it = handlers.erase(it);
			return;
		}
	}
}
