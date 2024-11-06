#include "loopManager.h"

#include "RenderSystem.h"
#include "SDLContext.h"
#include "ScriptSystem.h"
#include "api/event.h"
#include "api/eventHandler.h"
#include "api/eventManager.h"
#include "api/LoopTimer.h"
#include "keyCodes.h"

using namespace crepe::api;

LoopManager::LoopManager() {}
void LoopManager::processInput() {
	SDLContext::get_instance().handle_events(this->gameRunning);
}

void LoopManager::setRunning(bool running) { this->gameRunning = running; }

void LoopManager::fixedUpdate() {
	//fprintf(stderr, "fixed update\n");
}

void LoopManager::loop() {
	LoopTimer & timer = LoopTimer::getInstance();
	timer.start();

	while (gameRunning) {
		timer.update();

		while (timer.getLag() >= timer.getFixedDeltaTime()) {
			processInput();
			fixedUpdate();
			timer.advanceFixedUpdate();
		}

		update();
		render();

		timer.enforceFrameRate();
	}
}


void LoopManager::setup() {
	LoopTimer::getInstance().start();
	LoopTimer::getInstance().setFPS(60);
}

void LoopManager::render() {
	if (gameRunning) {
		RenderSystem::get_instance().update();
	}
}

void LoopManager::update() {
	LoopTimer & timer = LoopTimer::getInstance();
	float delta = timer.getDeltaTime();
	ScriptSystem::get_instance().update();
}
