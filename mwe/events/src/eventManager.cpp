#include "eventManager.h"

void EventManager::shutdown()
{
    subscribers.clear();
}

void EventManager::subscribe(int eventType, std::unique_ptr<IEventHandlerWrapper>&& handler, int eventId)
{
    if (eventId) {
        std::unordered_map<int, std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>>::iterator subscribers = subscribersByEventId.find(eventType);

        if (subscribers != subscribersByEventId.end()) {
            std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>& handlersMap = subscribers->second;
            std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlers = handlersMap.find(eventId);
            if (handlers != handlersMap.end()) {
                handlers->second.emplace_back(std::move(handler));
                return;
            }
        }
        subscribersByEventId[eventType][eventId].emplace_back(std::move(handler));

    } else {
        auto& handlers = subscribers[eventType];
    	handlers.emplace_back(std::move(handler));
    }
}

void EventManager::unsubscribe(int eventType, const std::string& handlerName, int eventId)
{
    if (eventId) {
        std::unordered_map<int, std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>>::iterator subscriberList = subscribersByEventId.find(eventType);
        if (subscriberList != subscribersByEventId.end()) {
            std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>& handlersMap = subscriberList->second;
            std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlers = handlersMap.find(eventId);
            if (handlers != handlersMap.end()) {
                std::vector<std::unique_ptr<IEventHandlerWrapper>>& callbacks = handlers->second;
                for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it = callbacks.begin(); it != callbacks.end(); ++it) {
                    if (it->get()->getType() == handlerName) {
                        it = callbacks.erase(it);
                        return;
                    }
                }
            }
        }
    } else {
        std::unordered_map<int, std::vector<std::unique_ptr<IEventHandlerWrapper>>>::iterator handlersIt = subscribers.find(eventType);
        if (handlersIt != subscribers.end()) {
            std::vector<std::unique_ptr<IEventHandlerWrapper>>& handlers = handlersIt->second;
            for (std::vector<std::unique_ptr<IEventHandlerWrapper>>::iterator it = handlers.begin(); it != handlers.end(); ++it) {
                if (it->get()->getType() == handlerName) {
                    it = handlers.erase(it);
                    return;
                }
            }
        }
    }
}

void EventManager::triggerEvent(const Event& event_, int eventId)
{
    if (eventId > 0) {
        auto handlersIt = subscribersByEventId[event_.getEventType()].find(eventId);
        if (handlersIt != subscribersByEventId[event_.getEventType()].end()) {
            std::vector<std::unique_ptr<IEventHandlerWrapper>>& callbacks = handlersIt->second;
            for (auto it = callbacks.begin(); it != callbacks.end();) {
                (*it)->exec(event_);
                if ((*it)->isDestroyOnSuccess()) {
                    it = callbacks.erase(it);
                } else {
                    ++it;
                }
            }
        }
    } else {
        auto& handlers = subscribers[event_.getEventType()];
        for (std::unique_ptr<IEventHandlerWrapper>& handler : handlers) {
            handler->exec(event_);
        }
    }
}

void EventManager::queueEvent(std::unique_ptr<Event>&& event_, int eventId)
{
    eventsQueue.emplace_back(std::move(event_), eventId);
}

void EventManager::dispatchEvents()
{
    for (std::vector<std::pair<std::unique_ptr<Event>, int>>::iterator eventIt = eventsQueue.begin(); eventIt != eventsQueue.end();) {
        if (!eventIt->first.get()->getHandled()) {
            triggerEvent(*eventIt->first.get(), eventIt->second);
            eventIt = eventsQueue.erase(eventIt);
        } else {
            ++eventIt;
        }
    }
}
