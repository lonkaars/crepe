
#include <typeindex>

#include "EventHandler.h"

namespace crepe {

// Implementation of EventHandlerWrapper constructor
template <typename EventType>
EventHandlerWrapper<EventType>::EventHandlerWrapper(const EventHandler<EventType> & handler)
	: handler(handler),
	  handler_type(handler.target_type().name()) {}

// Implementation of EventHandlerWrapper::call
template <typename EventType>
bool EventHandlerWrapper<EventType>::call(const Event & e) {
	return this->handler(static_cast<const EventType &>(e));
}

// Implementation of EventHandlerWrapper::get_type
template <typename EventType>
std::string EventHandlerWrapper<EventType>::get_type() const {
	return this->handler_type;
}

} //namespace crepe
