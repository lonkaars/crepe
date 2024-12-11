#include "../system/AnimatorSystem.h"
#include "../system/AudioSystem.h"
#include "../system/CollisionSystem.h"
#include "../system/InputSystem.h"
#include "../system/ParticleSystem.h"
#include "../system/PhysicsSystem.h"
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"
#include "../system/EventSystem.h"

#include "LoopManager.h"

using namespace crepe;
using namespace std;

LoopManager::LoopManager() {
	this->load_system<ScriptSystem>();
	this->load_system<PhysicsSystem>();
	this->load_system<CollisionSystem>();
	this->load_system<AnimatorSystem>();
	this->load_system<ParticleSystem>();
	this->load_system<RenderSystem>();
	this->load_system<InputSystem>();
	this->load_system<EventSystem>();
	this->load_system<AudioSystem>();
}

void LoopManager::start() {
	this->setup();
	this->loop();
}

void LoopManager::fixed_update() {
	for (auto & [type, system] : this->systems) {
		if (!system->active) continue;
		system->fixed_update();
	}
}

void LoopManager::frame_update() {
	for (auto & [type, system] : this->systems) {
		if (!system->active) continue;
		system->frame_update();
	}
}

void LoopManager::setup() {
	LoopTimer & timer = this->loop_timer;
	this->game_running = true;
	this->scene_manager.load_next_scene();
	timer.start();
	timer.set_fps(200);
}

void LoopManager::loop() {
	LoopTimer & timer = this->loop_timer;
	timer.start();

	while (game_running) {
		timer.update();

		while (timer.get_lag() >= timer.get_fixed_delta_time()) {
			this->fixed_update();
			timer.advance_fixed_update();
		}

		this->frame_update();
		timer.enforce_frame_rate();
	}
}

