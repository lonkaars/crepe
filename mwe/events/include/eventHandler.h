#pragma once
#include "event.h"
#include <iostream>
#include <functional>
template<typename EventType>
using EventHandler = std::function<void(const EventType& e)>;
class IEventHandlerWrapper{
public:
    void Exec(const Event& e)
    {
        Call(e);
    }

    virtual std::string GetType() const = 0;

private:
    virtual void Call(const Event& e) = 0;
};

template<typename EventType>
class EventHandlerWrapper : public IEventHandlerWrapper {
public:
    explicit EventHandlerWrapper(const EventHandler<EventType>& handler)
        : m_handler(handler)
        , m_handlerType(m_handler.target_type().name()) {};

private:
    void Call(const Event& e) override
    {
        if (e.GetEventType() == EventType::GetStaticEventType()) {
            m_handler(static_cast<const EventType&>(e));
        }
    }

    std::string GetType() const override { return m_handlerType; }

    EventHandler<EventType> m_handler;
    const std::string m_handlerType;
};
