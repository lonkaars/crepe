#include "EventManager.h"

namespace crepe {

template <typename EventType>
subscription_t EventManager::subscribe(const EventHandler<EventType> & callback, int channel) {
	subscription_counter++;
	std::type_index event_type = typeid(EventType);
	std::unique_ptr<EventHandlerWrapper<EventType>> handler
		= std::make_unique<EventHandlerWrapper<EventType>>(callback);
	std::vector<CallbackEntry> & handlers = this->subscribers[event_type];
	handlers.emplace_back(CallbackEntry{
		.callback = std::move(handler),
		.channel = channel,
		.id = subscription_counter
	});
	return subscription_counter;
}

template <typename EventType>
void EventManager::queue_event(const EventType & event, int channel) {
	static_assert(std::is_base_of<Event, EventType>::value,
				  "EventType must derive from Event");
	std::type_index event_type = typeid(EventType);

	auto event_ptr = std::make_unique<EventType>(event);

	this->events_queue.push_back(QueueEntry{.event = std::move(event_ptr),
											.channel = channel,
											.type = event_type});
}

template <typename EventType>
void EventManager::trigger_event(const EventType & event, int channel) {
	std::type_index event_type = typeid(EventType);

	auto handlers_it = this->subscribers.find(event_type);
	if (handlers_it != this->subscribers.end()) {
		const std::vector<CallbackEntry> & handlers = handlers_it->second;

		for (const CallbackEntry & handler : handlers) {
			if (handler.channel != channel && handler.channel != CHANNEL_ALL) {
				continue;
			}
			if (handler.callback->exec(event)) {
				break;
			}
		}
	}
}


} // namespace crepe
