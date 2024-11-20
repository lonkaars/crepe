#pragma once

#include "EventManager.h"

namespace crepe {

template <typename EventType>
subscription_t EventManager::subscribe(const EventHandler<EventType> & callback,
									   event_channel_t channel) {
	subscription_counter++;
	std::type_index event_type = typeid(EventType);
	std::unique_ptr<EventHandlerWrapper<EventType>> handler
		= std::make_unique<EventHandlerWrapper<EventType>>(callback);
	std::vector<CallbackEntry> & handlers = this->subscribers[event_type];
	handlers.emplace_back(CallbackEntry{
		.callback = std::move(handler), .channel = channel, .id = subscription_counter});
	return subscription_counter;
}

template <typename EventType>
void EventManager::queue_event(const EventType & event, event_channel_t channel) {
	static_assert(std::is_base_of<Event, EventType>::value,
				  "EventType must derive from Event");
	this->events_queue.push_back(QueueEntry{
		.event = std::make_unique<EventType>(event),
		.channel = channel,
		.type = typeid(EventType),
	});
}

template <typename EventType>
void EventManager::trigger_event(const EventType & event, event_channel_t channel) {
	this->handle_event(typeid(EventType), channel, event);
}

} // namespace crepe
