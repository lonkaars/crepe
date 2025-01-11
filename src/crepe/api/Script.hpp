#pragma once

#include "../manager/ComponentManager.h"
#include "../manager/ReplayManager.h"

#include "BehaviorScript.h"
#include "Script.h"

namespace crepe {

template <typename T>
T & Script::get_component() const {
	using namespace std;
	RefVector<T> all_components = this->get_components<T>();
	if (all_components.size() < 1)
		throw runtime_error(
			format("Script: no component found with type = {}", typeid(T).name())
		);

	return all_components.back().get();
}

template <typename T>
RefVector<T> Script::get_components() const {
	return this->get_components_by_id<T>(this->game_object_id);
}

template <class... Args>
void Script::logf(const Log::Level & level, std::format_string<Args...> fmt, Args &&... args) {
	Log::logf(level, fmt, std::forward<Args>(args)...);
}

template <class... Args>
void Script::logf(std::format_string<Args...> fmt, Args &&... args) {
	Log::logf(fmt, std::forward<Args>(args)...);
}

template <typename EventType>
void Script::subscribe_internal(
	const EventHandler<EventType> & callback, event_channel_t channel
) {
	EventManager & mgr = this->mediator->event_manager;
	subscription_t listener = mgr.subscribe<EventType>(
		[this, callback](const EventType & data) -> bool {
			// check if (parent) BehaviorScript component is active
			bool & active = this->active;
			if (!active) return false;

			// check if replay manager is playing (if initialized)
			try {
				ReplayManager & replay = this->mediator->replay_manager;
				if (replay.get_state() == ReplayManager::PLAYING) return false;
			} catch (const std::runtime_error &) {
			}

			// call user-provided callback
			return callback(data);
		},
		channel
	);
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

template <typename EventType>
void Script::trigger_event(const EventType & event, event_channel_t channel) {
	EventManager & mgr = this->mediator->event_manager;
	mgr.trigger_event(event, channel);
}

template <typename EventType>
void Script::queue_event(const EventType & event, event_channel_t channel) {
	EventManager & mgr = this->mediator->event_manager;
	mgr.queue_event(event, channel);
}

template <typename T>
RefVector<T> Script::get_components_by_id(game_object_id_t id) const {
	Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;

	return mgr.get_components_by_id<T>(id);
}
template <typename T>
RefVector<T> Script::get_components_by_name(const std::string & name) const {
	Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;

	return mgr.get_components_by_name<T>(name);
}
template <typename T>
RefVector<T> Script::get_components_by_tag(const std::string & tag) const {
	Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;

	return mgr.get_components_by_tag<T>(tag);
}

} // namespace crepe
