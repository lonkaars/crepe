#include "EventManager.h"

namespace crepe {

template <typename EventType>
void EventManager::subscribe(const EventHandler<EventType> & callback, int channel, int priority) {
	using HandlersVec = std::vector<CallbackEntry>;

	std::type_index event_type = typeid(EventType);
	std::unique_ptr<EventHandlerWrapper<EventType>> handler
		= std::make_unique<EventHandlerWrapper<EventType>>(callback);
	HandlersVec & handlers = this->subscribers[event_type];
	handlers.emplace_back(CallbackEntry{
		.callback = std::move(handler),
		.channel = channel,
		.priority = priority,
	});
}

template <typename EventType>
void EventManager::queue_event(const EventType & event, int channel,int priority) {
	static_assert(std::is_base_of<Event, EventType>::value, "EventType must derive from Event");
	std::type_index event_type = typeid(EventType);

	auto event_ptr = std::make_unique<EventType>(event);

	this->events_queue.push_back(
		QueueEntry{
			.event = std::move(event_ptr),
			.channel = channel,
			.type = event_type,
			.priority = priority
		}
	);
}

template <typename EventType>
void EventManager::trigger_event(const EventType & event, int channel) {
	using HandlersMap
		= std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>;
	using HandlersVec = std::vector<std::unique_ptr<IEventHandlerWrapper>>;

	std::type_index event_type = typeid(EventType);

	if (channel == CHANNEL_ALL) {
		HandlersMap & handlers_map = this->subscribers_by_event_id[event_type];
		auto handlers_it = handlers_map.find(channel);

		if (handlers_it != handlers_map.end()) {
			HandlersVec & handlers = handlers_it->second;
			for (auto it = handlers.begin(); it != handlers.end(); ++it) {
				// stops when callback returns true
				if ((*it)->exec(event)) {
					break;
				}
			}
		}
	} else {
		HandlersVec & handlers = this->subscribers[event_type];
		for (auto it = handlers.begin(); it != handlers.end(); ++it) {
			// stops when callback returns true
			if ((*it)->exec(event)) {
				break;
			}
		}
	}
}

template <typename EventType>
void EventManager::unsubscribe(const EventHandler<EventType> & callback, int channel) {
	using HandlersMap
		= std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>;
	using HandlersVec = std::vector<std::unique_ptr<IEventHandlerWrapper>>;

	std::type_index event_type = typeid(EventType);
	std::string handler_name = callback.target_type().name();

	if (channel) {
		auto subscriber_list = this->subscribers_by_event_id.find(event_type);
		if (subscriber_list != this->subscribers_by_event_id.end()) {
			HandlersMap & handlers_map = subscriber_list->second;
			auto handlers = handlers_map.find(channel);
			if (handlers != handlers_map.end()) {
				HandlersVec & callbacks = handlers->second;
				for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
					if ((*it)->get_type() == handler_name) {
						it = callbacks.erase(it);
						return;
					}
				}
			}
		}
	} else {
		auto handlers_it = this->subscribers.find(event_type);
		if (handlers_it != this->subscribers.end()) {
			HandlersVec & handlers = handlers_it->second;
			for (auto it = handlers.begin(); it != handlers.end(); ++it) {
				if ((*it)->get_type() == handler_name) {
					it = handlers.erase(it);
					return;
				}
			}
		}
	}
}

} // namespace crepe
