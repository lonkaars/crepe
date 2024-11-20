#include "EventManager.h"

namespace crepe {

template <typename EventType>
void EventManager::subscribe(const EventHandler<EventType> & callback, int channel,
							 int priority) {

	std::type_index event_type = typeid(EventType);
	std::unique_ptr<EventHandlerWrapper<EventType>> handler
		= std::make_unique<EventHandlerWrapper<EventType>>(callback);
	std::vector<CallbackEntry> & handlers = this->subscribers[event_type];
	handlers.emplace_back(CallbackEntry{
		.callback = std::move(handler),
		.channel = channel,
		.priority = priority,
	});
	// Sort handlers by priority (highest first)
	std::sort(handlers.begin(), handlers.end(),
			  [](const CallbackEntry & a, const CallbackEntry & b) {
				  return a.priority > b.priority;
			  });
}

template <typename EventType>
void EventManager::queue_event(const EventType & event, int channel, int priority) {
	static_assert(std::is_base_of<Event, EventType>::value,
				  "EventType must derive from Event");
	std::type_index event_type = typeid(EventType);

	auto event_ptr = std::make_unique<EventType>(event);

	this->events_queue.push_back(QueueEntry{.event = std::move(event_ptr),
											.channel = channel,
											.type = event_type,
											.priority = priority});
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

template <typename EventType>
void EventManager::unsubscribe(const EventHandler<EventType> & callback, int channel) {
	std::type_index event_type = typeid(EventType);
	std::string handler_name = callback.target_type().name();

	// Find the list of handlers for this event type
	auto handlers_it = this->subscribers.find(event_type);
	if (handlers_it != this->subscribers.end()) {
		std::vector<CallbackEntry> & handlers = handlers_it->second;

		for (auto it = handlers.begin(); it != handlers.end();) {
			// Match based on handler type and channel
			if (it->callback->get_type() == handler_name && it->channel == channel) {
				it = handlers.erase(it);
				return;
			}
			++it;
		}
	}
}

} // namespace crepe
