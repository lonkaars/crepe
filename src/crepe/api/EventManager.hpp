#include "EventManager.h"
namespace crepe {

template <typename EventType>
void EventManager::subscribe(EventHandler<EventType> && callback, int channel) {
	std::type_index event_type = typeid(EventType);
	std::unique_ptr<EventHandlerWrapper<EventType>> handler
		= std::make_unique<EventHandlerWrapper<EventType>>(callback);

	if (channel) {
		std::unordered_map<int,
						   std::vector<std::unique_ptr<IEventHandlerWrapper>>> &
			handlers_map
			= this->subscribers_by_event_id[event_type];
		std::unordered_map<
			int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator
			handlers
			= handlers_map.find(channel);
		if (handlers != handlers_map.end()) {
			handlers->second.emplace_back(std::move(handler));
		} else {
			handlers_map[channel].emplace_back(std::move(handler));
		}
	} else {
		std::vector<std::unique_ptr<IEventHandlerWrapper>> & handlers
			= this->subscribers[event_type];
		handlers.emplace_back(std::move(handler));
	}
}

template <typename EventType>
void EventManager::queue_event(EventType && event, int channel) {
	std::type_index event_type = std::type_index(typeid(EventType));

	std::unique_ptr<EventType> event_ptr
		= std::make_unique<EventType>(std::forward<EventType>(event));

	std::tuple<std::unique_ptr<Event>, int, std::type_index> tuple(
		std::move(event_ptr), channel, event_type);
	this->events_queue.push_back(std::move(tuple));
}

template <typename EventType>
void EventManager::trigger_event(const EventType & event, int channel) {
	std::type_index event_type = std::type_index(typeid(EventType));

	if (channel > 0) {
		std::unordered_map<int,
						   std::vector<std::unique_ptr<IEventHandlerWrapper>>> &
			handlers_map
			= this->subscribers_by_event_id[event_type];
		std::unordered_map<
			int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator
			handlers_it
			= handlers_map.find(channel);

		if (handlers_it != handlers_map.end()) {
			std::vector<std::unique_ptr<IEventHandlerWrapper>> & handlers
				= handlers_it->second;
			for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it
				 = handlers.begin();
				 it != handlers.end();++it) {
				// stops when callback returns true
				if((*it)->exec(event)){
					break;
				}
			}
		}
	} else {
		std::vector<std::unique_ptr<IEventHandlerWrapper>> & handlers
			= this->subscribers[event_type];
		for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it
			 = handlers.begin();
			 it != handlers.end();++it) {
			// stops when callback returns true
			if((*it)->exec(event)){
					break;
				}
		}
	}
}

template <typename EventType>
void EventManager::unsubscribe(const EventHandler<EventType> & callback,
							   int channel) {
	std::type_index event_type(typeid(EventType));
	std::string handler_name = callback.target_type().name();

	if (channel) {
		std::unordered_map<
			std::type_index,
			std::unordered_map<
				int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>>::
			iterator subscriber_list
			= this->subscribers_by_event_id.find(event_type);
		if (subscriber_list != this->subscribers_by_event_id.end()) {
			std::unordered_map<
				int, std::vector<std::unique_ptr<IEventHandlerWrapper>>> &
				handlers_map
				= subscriber_list->second;
			std::unordered_map<
				int,
				std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator
				handlers
				= handlers_map.find(channel);
			if (handlers != handlers_map.end()) {
				std::vector<std::unique_ptr<IEventHandlerWrapper>> & callbacks
					= handlers->second;
				for (std::vector<
						 std::unique_ptr<IEventHandlerWrapper>>::iterator it
					 = callbacks.begin();
					 it != callbacks.end(); ++it) {
					if ((*it)->get_type() == handler_name) {
						it = callbacks.erase(it);
						return;
					}
				}
			}
		}
	} else {
		std::unordered_map<std::type_index,
						   std::vector<std::unique_ptr<IEventHandlerWrapper>>>::
			iterator handlers_it
			= this->subscribers.find(event_type);
		if (handlers_it != this->subscribers.end()) {
			std::vector<std::unique_ptr<IEventHandlerWrapper>> & handlers
				= handlers_it->second;
			for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it
				 = handlers.begin();
				 it != handlers.end(); ++it) {
				if ((*it)->get_type() == handler_name) {
					it = handlers.erase(it);
					return;
				}
			}
		}
	}
}

}
