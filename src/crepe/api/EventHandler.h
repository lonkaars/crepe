#pragma once
#include <functional>
#include <iostream>
#include <typeindex>
#include "Event.h"

template <typename EventType>
using EventHandler = std::function<bool(const EventType & e)>;

class IEventHandlerWrapper {
public:
    virtual ~IEventHandlerWrapper() = default;

    bool exec(const Event & e);

    virtual std::string get_type() const = 0;

private:
    virtual bool call(const Event & e) = 0;
};

template <typename EventType>
class EventHandlerWrapper : public IEventHandlerWrapper {
public:
    explicit EventHandlerWrapper(const EventHandler<EventType> & handler)
        : m_handler(handler), m_handler_type(m_handler.target_type().name()) {
    }

private:
    bool call(const Event & e) override {
        return m_handler(static_cast<const EventType &>(e));
    }

    std::string get_type() const override { return m_handler_type; }

    EventHandler<EventType> m_handler;
    const std::string m_handler_type;
};
