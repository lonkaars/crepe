#include "EventManager.h"

namespace crepe {

template <typename EventType>
void EventManager::subscribe(EventHandler<EventType> && callback, int channel) {
	using HandlersMap = std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>;
	using HandlersVec = std::vector<std::unique_ptr<IEventHandlerWrapper>>;

	std::type_index event_type = typeid(EventType);
	std::unique_ptr<EventHandlerWrapper<EventType>> handler
		= std::make_unique<EventHandlerWrapper<EventType>>(callback);

	if (channel) {
		HandlersMap & handlers_map = this->subscribers_by_event_id[event_type];
		auto handlers = handlers_map.find(channel);
		if (handlers != handlers_map.end()) {
			handlers->second.emplace_back(std::move(handler));
		} else {
			handlers_map[channel].emplace_back(std::move(handler));
		}
	} else {
		HandlersVec & handlers = this->subscribers[event_type];
		handlers.emplace_back(std::move(handler));
	}
}

template <typename EventType>
void EventManager::queue_event(EventType && event, int channel) {
	std::type_index event_type = std::type_index(typeid(EventType));

	auto event_ptr = std::make_unique<EventType>(std::forward<EventType>(event));

	std::tuple<std::unique_ptr<Event>, int, std::type_index> tuple(
		std::move(event_ptr), channel, event_type);
	this->events_queue.push_back(std::move(tuple));
}

template <typename EventType>
void EventManager::trigger_event(const EventType & event, int channel) {
	using HandlersMap = std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>;
	using HandlersVec = std::vector<std::unique_ptr<IEventHandlerWrapper>>;

	std::type_index event_type = std::type_index(typeid(EventType));

	if (channel > 0) {
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
	using HandlersMap = std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>;
	using HandlersVec = std::vector<std::unique_ptr<IEventHandlerWrapper>>;

	std::type_index event_type(typeid(EventType));
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
