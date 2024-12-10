#include "../facade/SDLContext.h"
#include "../manager/EventManager.h"
#include "../system/AnimatorSystem.h"
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
	this->event_manager.subscribe<ShutDownEvent>(
		[this](const ShutDownEvent & event) { return this->on_shutdown(event); });
}

void LoopManager::process_input() {
	this->get_system<InputSystem>().update();
	this->event_manager.dispatch_events();
}

void LoopManager::start() {
	this->setup();
	this->loop();
}

void LoopManager::fixed_update() {
	this->get_system<ScriptSystem>().update();
	this->get_system<PhysicsSystem>().update();
	this->get_system<CollisionSystem>().update();
}

void LoopManager::loop() {

	while (game_running) {
		this->loop_timer.update();

		while (this->loop_timer.get_lag() >= this->loop_timer.get_fixed_delta_time()) {
			this->process_input();
			this->fixed_update();
			this->loop_timer.advance_fixed_update();
		}

		this->frame_update();
		this->render();
		this->loop_timer.enforce_frame_rate();
	}
}

void LoopManager::setup() {
	this->game_running = true;
	this->loop_timer.start();
	this->scene_manager.load_next_scene();
}

void LoopManager::render() {
	if (!this->game_running) return;

	this->get_system<AnimatorSystem>().update();
	this->get_system<RenderSystem>().update();
}

bool LoopManager::on_shutdown(const ShutDownEvent & e) {
	this->game_running = false;
	return false;
}

void LoopManager::frame_update() {
	this->scene_manager.load_next_scene();
}
