#include "../system/AnimatorSystem.h"
#include "../system/AudioSystem.h"
#include "../system/CollisionSystem.h"
#include "../system/InputSystem.h"
#include "../system/ParticleSystem.h"
#include "../system/PhysicsSystem.h"
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"
#include "manager/EventManager.h"

#include "LoopManager.h"

using namespace crepe;
using namespace std;

LoopManager::LoopManager() {
	this->load_system<AnimatorSystem>();
	this->load_system<CollisionSystem>();
	this->load_system<ParticleSystem>();
	this->load_system<PhysicsSystem>();
	this->load_system<RenderSystem>();
	this->load_system<ScriptSystem>();
	this->load_system<InputSystem>();
	this->load_system<AudioSystem>();
}

void LoopManager::process_input() { this->get_system<InputSystem>().update(); }

void LoopManager::start() {
	this->setup();
	this->loop();
}
void LoopManager::set_running(bool running) { this->game_running = running; }

void LoopManager::fixed_update() {
	// TODO: retrieve EventManager from direct member after singleton refactor
	EventManager & ev = this->mediator.event_manager;
	ev.dispatch_events();
	this->get_system<ScriptSystem>().update();
	this->get_system<PhysicsSystem>().update();
	this->get_system<CollisionSystem>().update();
	this->get_system<AudioSystem>().update();
}

void LoopManager::loop() {
	LoopTimer & timer = this->loop_timer;
	timer.start();

	while (game_running) {
		timer.update();

		while (timer.get_lag() >= timer.get_fixed_delta_time()) {
			this->process_input();
			this->fixed_update();
			timer.advance_fixed_update();
		}

		this->update();
		this->render();

		timer.enforce_frame_rate();
	}
}

void LoopManager::setup() {
	LoopTimer & timer = this->loop_timer;
	this->game_running = true;
	this->scene_manager.load_next_scene();
	timer.start();
	timer.set_fps(200);
}

void LoopManager::render() {
	if (!this->game_running) return;

	this->get_system<AnimatorSystem>().update();
	this->get_system<RenderSystem>().update();
}

void LoopManager::update() {}
