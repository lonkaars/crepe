#include "loopManager.h"
#include "timer.h"
using namespace crepe;
LoopManager::LoopManager() {

}
LoopManager::~LoopManager() {
}
void LoopManager::process_input() {
}
void LoopManager::fixed_update() { 
}
void LoopManager::loop() {
	LoopTimer & timer = LoopTimer::getInstance();

	while (gameRunning) {
		timer.update();
		process_input();
		while (timer.getLag() >= timer.getFixedDeltaTime()) {
			
			fixed_update();
			timer.advanceFixedUpdate();
		}

		update();
		render();

		timer.enforceFrameRate();
	}

}

void LoopManager::setup() {

	LoopTimer::getInstance().start();
	this->gameRunning = true;
}
void LoopManager::render() {
	if (gameRunning) {
	}
}

void LoopManager::update() {
	LoopTimer & timer = LoopTimer::getInstance();

	float delta = timer.getDeltaTime();
}
void LoopManager::start(){
	this->setup();
	this->loop();
}
