#pragma once
#include <unordered_map>
#include <memory>
#include "event.h"
#include "eventHandler.h"
using EventType = int;
using EventId = int;
class EventManager{
	public: 
		
		void subscribe(EventId eventId,std::unique_ptr<IEventHandlerWrapper>&& handler);
		void unsubscribe(EventId eventId, const std::string& handlerName);
		void dispatchEvents();
		void triggerEvent(EventId eventId);
		void queueEvent();
	private:
		std::unordered_map<EventType, std::vector<std::unique_ptr<IEventHandlerWrapper>>> m_subscribers;
};
