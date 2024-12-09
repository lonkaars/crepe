#pragma once

#include "../manager/ComponentManager.h"

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <typename T>
T & Script::get_component() const {
	using namespace std;
	RefVector<T> all_components = this->get_components<T>();
	if (all_components.size() < 1)
		throw runtime_error(
			format("Script: no component found with type = {}", typeid(T).name()));

	return all_components.back().get();
}

template <typename T>
RefVector<T> Script::get_components() const {
	ComponentManager & mgr = this->mediator->component_manager;

	return mgr.get_components_by_id<T>(this->game_object_id);
}

template <typename... Args>
void Script::logf(Args &&... args) {
	Log::logf(std::forward<Args>(args)...);
}

template <typename EventType>
void Script::subscribe_internal(const EventHandler<EventType> & callback,
								event_channel_t channel) {
	EventManager & mgr = this->mediator->event_manager;
	subscription_t listener = mgr.subscribe<EventType>(
		[this, callback](const EventType & data) -> bool {
			bool & active = this->active;
			if (!active) return false;
			return callback(data);
		},
		channel);
	this->listeners.push_back(listener);
}

template <typename EventType>
void Script::subscribe(const EventHandler<EventType> & callback, event_channel_t channel) {
	this->subscribe_internal(callback, channel);
}

template <typename EventType>
void Script::subscribe(const EventHandler<EventType> & callback) {
	this->subscribe_internal(callback, EventManager::CHANNEL_ALL);
}

} // namespace crepe
