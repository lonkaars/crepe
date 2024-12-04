#include <iostream>

#include "../facade/SDLContext.h"

#include "../system/AnimatorSystem.h"
#include "../system/CollisionSystem.h"
#include "../system/ParticleSystem.h"
#include "../system/PhysicsSystem.h"
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"
#include "../api/EventManager.h"
#include "LoopManager.h"
#include "LoopTimer.h"
#include <iostream>
using namespace crepe;
using namespace std;

LoopManager::LoopManager() {
	this->loop_timer = make_unique<LoopTimer>();
	this->load_system<AnimatorSystem>();
	this->load_system<CollisionSystem>();
	this->load_system<ParticleSystem>();
	this->load_system<PhysicsSystem>();
	this->load_system<RenderSystem>();
	this->load_system<ScriptSystem>();
	EventManager::get_instance().subscribe<ShutDownEvent>([this](const ShutDownEvent& event) {
    	return this->on_shutdown(event);
	});

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
	this->loop_timer->set_target_fps(60);
}

void LoopManager::render() {
	if (this->game_running) {
		//this->get_system<RenderSystem>().update();
	}
}
bool LoopManager::on_shutdown(const ShutDownEvent & e){
	this->game_running = false;
	return false;
}

void LoopManager::update() {
	std::cout << this->loop_timer->get_fps() << std::endl;
}
