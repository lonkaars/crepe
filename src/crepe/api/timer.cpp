#include "timer.h"


//TODO remove this include
#include <SDL2/SDL.h>
using namespace crepe::api;

LoopTimer::LoopTimer() {}
LoopTimer & LoopTimer::getInstance() {
	static LoopTimer instance;
	return instance;
}

void LoopTimer::start() {
	lastFrameTime = SDL_GetTicks64();
	elapsedTime = 0;
	elapsedFixedTime = 0;
	deltaTime = 0;
}

// Update the timer, calculate deltaTime
void LoopTimer::update() {
	uint64_t currentFrameTime = SDL_GetTicks64();
	deltaTime = (currentFrameTime - lastFrameTime) / 1000.0;

	if (deltaTime > maximumDeltaTime) {
		deltaTime = maximumDeltaTime;
	}

	elapsedTime += deltaTime;
	lastFrameTime = currentFrameTime;
}

double LoopTimer::getDeltaTime() const { return deltaTime; }
int LoopTimer::getCurrentTime() const { return SDL_GetTicks(); }

void LoopTimer::advanceFixedUpdate() { elapsedFixedTime += fixedDeltaTime; }

double LoopTimer::getFixedDeltaTime() const { return fixedDeltaTime; }

void LoopTimer::setFPS(int FPS) {
	this->FPS = FPS;
	frameTargetTime = 1.0 / FPS;
}

int LoopTimer::getFPS() const { return FPS; }

void LoopTimer::enforceFrameRate() {
	uint64_t currentFrameTime = SDL_GetTicks64();
	double frameDuration = (currentFrameTime - lastFrameTime) / 1000.0;

	if (frameDuration < frameTargetTime) {
		uint32_t delayTime
			= (uint32_t) ((frameTargetTime - frameDuration) * 1000.0);
		SDL_Delay(delayTime);
	}
}
double LoopTimer::getLag() const { return elapsedTime - elapsedFixedTime; }
