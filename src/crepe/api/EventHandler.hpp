
#include <typeindex>

#include "EventHandler.h"

namespace crepe {

// Implementation of EventHandlerWrapper constructor
template <typename EventType>
EventHandlerWrapper<EventType>::EventHandlerWrapper(
	const EventHandler<EventType> & handler)
	: m_handler(handler),
	  m_handler_type(m_handler.target_type().name()) {}

// Implementation of EventHandlerWrapper::call
template <typename EventType>
bool EventHandlerWrapper<EventType>::call(const Event & e) {
	return m_handler(static_cast<const EventType &>(e));
}

// Implementation of EventHandlerWrapper::get_type
template <typename EventType>
std::string EventHandlerWrapper<EventType>::get_type() const {
	return m_handler_type;
}

} //namespace crepe
