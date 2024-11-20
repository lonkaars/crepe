#pragma once

#include "../ComponentManager.h"

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <typename T>
T & Script::get_component() const {
	using namespace std;
	vector<reference_wrapper<T>> all_components = this->get_components<T>();
	if (all_components.size() < 1)
		throw runtime_error(
			format("Script: no component found with type = {}", typeid(T).name()));

	return all_components.back().get();
}

template <typename T>
std::vector<std::reference_wrapper<T>> Script::get_components() const {
	ComponentManager & mgr = *this->component_manager_ref;

	return mgr.get_components_by_id<T>(this->game_object_id);
}

template <typename... Args>
void Script::logf(Args &&... args) {
	Log::logf(std::forward<Args>(args)...);
}

template <typename EventType>
void Script::subscribe_internal(const EventHandler<EventType> & callback, event_channel_t channel) {
	EventManager & mgr = *this->event_manager_ref;
	subscription_t listener = mgr.subscribe<EventType>(callback, channel);
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
