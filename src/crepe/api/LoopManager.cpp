#include "../facade/SDLContext.h"

#include "../manager/EventManager.h"
#include "../system/AnimatorSystem.h"
#include "../system/CollisionSystem.h"
#include "../system/ParticleSystem.h"
#include "../system/PhysicsSystem.h"
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"

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
	EventManager::get_instance().subscribe<ShutDownEvent>(
		[this](const ShutDownEvent & event) { return this->on_shutdown(event); });
	this->loop_timer = make_unique<LoopTimer>();
	this->mediator.loop_timer = *loop_timer;
}

void LoopManager::process_input() { 
	
	this->sdl_context.handle_events(this->game_running); }

void LoopManager::start() {
	this->setup();
	this->loop();
}

void LoopManager::fixed_update() {}

void LoopManager::loop() {
	this->loop_timer->start();

	while (game_running) {
		this->loop_timer->update();

		while (this->loop_timer->get_lag() >= this->loop_timer->get_fixed_delta_time()) {
			this->process_input();
			this->fixed_update();
			this->loop_timer->advance_fixed_update();
		}

		this->update();
		this->render();
		this->loop_timer->enforce_frame_rate();
	}
}

void LoopManager::setup() {

	this->game_running = true;
	this->loop_timer->start();
}

void LoopManager::render() {
	if (!this->game_running) return;

	this->get_system<RenderSystem>().update();
}
bool LoopManager::on_shutdown(const ShutDownEvent & e) {
	this->game_running = false;
	return false;
}

void LoopManager::update() {}
