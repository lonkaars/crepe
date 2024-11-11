#include "EventManager.h"

void EventManager::unsubscribe(std::type_index eventType, const std::string & handlerName,
							   int eventId) {
	// if (eventId) {
	// 	std::unordered_map<
	// 		std::type_index, std::unordered_map<
	// 				 int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>>::iterator subscriber_list = subscribers_by_event_id.find(eventType);
	// 	if (subscriber_list != subscribers_by_event_id.end()) {
	// 		std::unordered_map<
	// 			int, std::vector<std::unique_ptr<IEventHandlerWrapper>>> &
	// 			handlers_map
	// 			= subscriber_list->second;
	// 		std::unordered_map<
	// 			int,
	// 			std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator
	// 			handlers
	// 			= handlers_map.find(eventId);
	// 		if (handlers != handlers_map.end()) {
	// 			std::vector<std::unique_ptr<IEventHandlerWrapper>> & callbacks
	// 				= handlers->second;
	// 			for (std::vector<
	// 					 std::unique_ptr<IEventHandlerWrapper>>::iterator it
	// 				 = callbacks.begin();
	// 				 it != callbacks.end(); ++it) {
	// 				if (it->get()->getType() == handlerName) {
	// 					it = callbacks.erase(it);
	// 					return;
	// 				}
	// 			}
	// 		}
	// 	}
	// } else {
	// 	std::unordered_map<
	// 		std::type_index, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator
	// 		handlers_it
	// 		= subscribers.find(eventType);
	// 	if (handlers_it != subscribers.end()) {
	// 		std::vector<std::unique_ptr<IEventHandlerWrapper>> & handlers
	// 			= handlers_it->second;
	// 		for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it
	// 			 = handlers.begin();
	// 			 it != handlers.end(); ++it) {
	// 			if (it->get()->getType() == handlerName) {
	// 				it = handlers.erase(it);
	// 				return;
	// 			}
	// 		}
	// 	}
	// }
}

void EventManager::queue_event(std::unique_ptr<Event> && event_, int eventId) {
	events_queue.emplace_back(std::move(event_), eventId);
}

void EventManager::dispatch_events() {
	// for (std::vector<std::pair<std::unique_ptr<Event>, int>>::iterator eventIt
	// 	 = eventsQueue.begin();
	// 	 eventIt != eventsQueue.end();) {
	// 	bool handled = false;
	// 	if (!handled) {
	// 		triggerEvent(*eventIt->first.get(), eventIt->second);
	// 		eventIt = eventsQueue.erase(eventIt);
	// 	} else {
	// 		++eventIt;
	// 	}
	// }
}
