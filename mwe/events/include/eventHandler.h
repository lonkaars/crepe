#pragma once

#include "event.h"

#include <functional>
#include <iostream>
template <typename EventType>
using EventHandler = std::function<void(const EventType & e)>;

class IEventHandlerWrapper {
public:
	virtual ~IEventHandlerWrapper() = default;

	void exec(const Event & e);

	virtual std::string getType() const = 0;
	virtual bool isDestroyOnSuccess() const = 0;

private:
	virtual void call(const Event & e) = 0;
};

template <typename EventType>
class EventHandlerWrapper : public IEventHandlerWrapper {
public:
	explicit EventHandlerWrapper(const EventHandler<EventType> & handler,
								 const bool destroyOnSuccess = false)
		: m_handler(handler), m_handlerType(m_handler.target_type().name()),
		  m_destroyOnSuccess(destroyOnSuccess) {
		// std::cout << m_handlerType << std::endl;
	}

private:
	void call(const Event & e) override {
		if (e.getEventType() == EventType::getStaticEventType()) {
			m_handler(static_cast<const EventType &>(e));
		}
	}

	std::string getType() const override { return m_handlerType; }
	bool isDestroyOnSuccess() const { return m_destroyOnSuccess; }

	EventHandler<EventType> m_handler;
	const std::string m_handlerType;
	bool m_destroyOnSuccess{false};
};
