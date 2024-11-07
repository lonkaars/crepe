#include "api/LoopManager.h"

#include "RenderSystem.h"
#include "SDLContext.h"
#include "ScriptSystem.h"
#include "api/event.h"
#include "api/eventHandler.h"
#include "api/eventManager.h"
#include "api/LoopTimer.h"
#include "keyCodes.h"

namespace crepe::api {

LoopManager::LoopManager() {}
LoopManager::~LoopManager() {}
void LoopManager::process_input() {
	SDLContext::get_instance().handle_events(this->gameRunning);
}
void LoopManager::start(){
	this->setup();
	this->loop();
}
void LoopManager::set_running(bool running) { this->gameRunning = running; }

void LoopManager::fixed_update() {
	//fprintf(stderr, "fixed update\n");
}

void LoopManager::loop() {
	LoopTimer & timer = LoopTimer::getInstance();
	timer.start();

	while (gameRunning) {
		timer.update();

		while (timer.get_lag() >= timer.get_fixed_delta_time()) {
			process_input();
			fixed_update();
			timer.advance_fixed_update();
		}

		update();
		render();

		timer.enforce_frame_rate();
	}
}


void LoopManager::setup() {
	this->gameRunning = true;
	LoopTimer::getInstance().start();
	LoopTimer::getInstance().set_fps(60);
}

void LoopManager::render() {
	if (gameRunning) {
		RenderSystem::get_instance().update();
	}
}

void LoopManager::update() {
	LoopTimer & timer = LoopTimer::getInstance();
	ScriptSystem::get_instance().update();
}

} // namespace crepe::api
