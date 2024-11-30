#include "../facade/SDLContext.h"

#include "../system/AnimatorSystem.h"
#include "../system/CollisionSystem.h"
#include "../system/ParticleSystem.h"
#include "../system/PhysicsSystem.h"
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"

#include "LoopManager.h"
#include "LoopTimer.h"

using namespace crepe;
using namespace std;

LoopManager::LoopManager() {
	this->load_system<AnimatorSystem>();
	this->load_system<CollisionSystem>();
	this->load_system<ParticleSystem>();
	this->load_system<PhysicsSystem>();
	this->load_system<RenderSystem>();
	this->load_system<ScriptSystem>();
}

void LoopManager::process_input() {
	SDLContext::get_instance().handle_events(this->game_running);
}

void LoopManager::start() {
	this->setup();
	this->loop();
}
void LoopManager::set_running(bool running) { this->game_running = running; }

void LoopManager::fixed_update() {}

void LoopManager::loop() {
	LoopTimer & timer = LoopTimer::get_instance();
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
	this->game_running = true;
	LoopTimer::get_instance().start();
	LoopTimer::get_instance().set_fps(200);
	this->scene_manager.load_next_scene();
}

void LoopManager::render() {
	if (this->game_running) {
		this->get_system<RenderSystem>().update();
	}
}

void LoopManager::update() {
	LoopTimer & timer = LoopTimer::get_instance();
	this->get_system<AnimatorSystem>().update();
}
