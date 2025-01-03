#pragma once
#include "event.h"
#include "eventHandler.h"
#include "keyCodes.h"
#include <memory>
#include <unordered_map>
#include <vector>
// using EventType = std::uint32_t;
// using EventId = std::uint64_t;

class EventManager {
public:
	EventManager(const EventManager &) = delete;
	const EventManager & operator=(const EventManager &) = delete;
	static EventManager & getInstance() {
		static EventManager instance;
		return instance;
	}

	void shutdown();
	void
	subscribe(int eventType, std::unique_ptr<IEventHandlerWrapper> && handler, int eventId);
	void unsubscribe(int eventType, const std::string & handlerName, int eventId);
	void triggerEvent(const Event & event_, int eventId);
	void queueEvent(std::unique_ptr<Event> && event_, int eventId);
	void dispatchEvents();

private:
	EventManager() = default;
	std::vector<std::pair<std::unique_ptr<Event>, int>> eventsQueue;
	std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>> subscribers;
	std::unordered_map<
		int, std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>>
		subscribersByEventId;
};

template <typename EventType>
inline void subscribe(
	const EventHandler<EventType> & callback, int eventId = 0,
	const bool unsubscribeOnSuccess = false
) {
	std::unique_ptr<IEventHandlerWrapper> handler
		= std::make_unique<EventHandlerWrapper<EventType>>(callback, unsubscribeOnSuccess);
	EventManager::getInstance().subscribe(
		EventType::getStaticEventType(), std::move(handler), eventId
	);
}

template <typename EventType>
inline void unsubscribe(const EventHandler<EventType> & callback, int eventId = 0) {
	const std::string handlerName = callback.target_type().name();
	EventManager::getInstance().unsubscribe(
		EventType::getStaticEventType(), handlerName, eventId
	);
}

inline void triggerEvent(const Event & triggeredEvent, int eventId = 0) {
	EventManager::getInstance().triggerEvent(triggeredEvent, eventId);
}

inline void queueEvent(std::unique_ptr<Event> && queuedEvent, int eventId = 0) {
	EventManager::getInstance().queueEvent(
		std::forward<std::unique_ptr<Event>>(queuedEvent), eventId
	);
}
