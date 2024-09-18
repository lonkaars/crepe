#include "timer.h"

// Singleton instance for global access
LoopTimer& LoopTimer::getInstance() {
    static LoopTimer instance;
    return instance;
}

// Private constructor
LoopTimer::LoopTimer() : lastTime(0), deltaTime(0), frequency(0), FPS(0), frameTargetTime(0) {}

void LoopTimer::start() {

}

void LoopTimer::update() {
    Uint64 currentTime = SDL_GetTicks64();
    deltaTime = (currentTime - lastFrameTime) / 1000.0;
	time += deltaTime;
    lastFrameTime = currentTime;
}

float LoopTimer::getDeltaTime() const {
    return deltaTime;
}
float LoopTimer::getDeltaTimeMs() const {
    return deltaTime * 1000;
}
int LoopTimer::getCurrentTime() const {
    return SDL_GetTicks64();
}

float LoopTimer::getFixedDeltaTime() const {
    return fixedDeltaTime;
}

void LoopTimer::setFPS(int FPS) {
    if (FPS > 0) {
        this->FPS = FPS;
        frameTargetTime = 1000 / FPS;
    }
}
float LoopTimer::getLag() const{
	return lag;
}
int LoopTimer::getFPS() const {
    return FPS;
}

// Delay to match target frame time
void LoopTimer::enforceFrameRate() {
    int waitTime = frameTargetTime - (SDL_GetTicks64() - lastFrameTime);
	if(waitTime > 0 && waitTime <= frameTargetTime){
		SDL_Delay(waitTime);
	}
}
