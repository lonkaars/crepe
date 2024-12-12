#include <string>

#include "../manager/SceneManager.h"

#include "Script.h"

using namespace crepe;
using namespace std;

Script::~Script() {
	EventManager & mgr = this->mediator->event_manager;
	for (auto id : this->listeners) {
		mgr.unsubscribe(id);
	}
}

template <>
void Script::subscribe(const EventHandler<CollisionEvent> & callback) {
	this->subscribe_internal(callback, this->game_object_id);
}

void Script::set_next_scene(const string & name) {
	SceneManager & mgr = this->mediator->scene_manager;
	mgr.set_next_scene(name);
}

SaveManager & Script::get_save_manager() const { return this->mediator->save_manager; }

void Script::replay::record_start() {
	ReplayManager & mgr = this->mediator->replay_manager;
	return mgr.record_start();
}

recording_t Script::replay::record_end() {
	ReplayManager & mgr = this->mediator->replay_manager;
	return mgr.record_end();
}

void Script::replay::play(recording_t recording) {
	ReplayManager & mgr = this->mediator->replay_manager;
	return mgr.play(recording);
}

void Script::replay::release(recording_t recording) {
	ReplayManager & mgr = this->mediator->replay_manager;
	return mgr.release(recording);
}
