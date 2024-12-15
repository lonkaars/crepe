#pragma once

#include "../util/Log.h"

#include "Scene.h"

namespace crepe {

template <class... Args>
void Scene::logf(const Log::Level & level, std::format_string<Args...> fmt, Args &&... args) {
	Log::logf(level, fmt, std::forward<Args>(args)...);
}

template <class... Args>
void Scene::logf(std::format_string<Args...> fmt, Args &&... args) {
	Log::logf(fmt, std::forward<Args>(args)...);
}

// template <typename EventType>
// void Scene::queue_event(const EventType & event, event_channel_t channel) {
// 	this->mediator->event_manager->queue_event(event,channel);
// }

// template <typename EventType>
// void Scene::trigger_event(const EventType & event, event_channel_t channel) {
// 	this->mediator->event_manager->trigger_event(event,channel);
// }

} // namespace crepe
