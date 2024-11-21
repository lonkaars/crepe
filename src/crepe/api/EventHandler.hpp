#include <typeindex>

#include "EventHandler.h"

namespace crepe {

// Implementation of EventHandlerWrapper constructor
template <typename EventType>
EventHandlerWrapper<EventType>::EventHandlerWrapper(const EventHandler<EventType> & handler)
	: handler(handler) {}

// Implementation of EventHandlerWrapper::call
template <typename EventType>
bool EventHandlerWrapper<EventType>::call(const Event & e) {
	return this->handler(static_cast<const EventType &>(e));
}

} //namespace crepe
