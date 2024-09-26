#include "timer.h"

// Constructor (private)
LoopTimer::LoopTimer(){}

// Get the singleton instance of the timer
LoopTimer& LoopTimer::getInstance() {
    static LoopTimer instance;
    return instance;
}

// Start the timer (initialize frame time)
void LoopTimer::start() {
    lastFrameTime = SDL_GetTicks64();
    elapsedTime = 0;
    elapsedFixedTime = 0;
    deltaTime = 0;
}

// Update the timer, calculate deltaTime
void LoopTimer::update() {
    uint64_t currentFrameTime = SDL_GetTicks64();
    deltaTime = (currentFrameTime - lastFrameTime) / 1000.0;  // Convert to seconds

    if (deltaTime > maximumDeltaTime) {
        deltaTime = maximumDeltaTime;
    }
	deltaTime *= gameScale;
    elapsedTime += deltaTime;
    lastFrameTime = currentFrameTime;
}

double LoopTimer::getDeltaTime() const {
    return deltaTime;
}
int LoopTimer::getCurrentTime() const {
    return SDL_GetTicks();
}

void LoopTimer::advanceFixedUpdate() {
    elapsedFixedTime += fixedDeltaTime;
}

double LoopTimer::getFixedDeltaTime() const {
    return fixedDeltaTime;
}

void LoopTimer::setFPS(int FPS) {
    this->FPS = FPS;
    frameTargetTime = 1.0 / FPS;
}

int LoopTimer::getFPS() const {
    return FPS;
}
void LoopTimer::setGameScale(double value){
	gameScale = value;
};
double LoopTimer::getGameScale(){
	return gameScale;
}
void LoopTimer::enforceFrameRate() {
    uint64_t currentFrameTime = SDL_GetTicks64();
    double frameDuration = (currentFrameTime - lastFrameTime) / 1000.0;

    if (frameDuration < frameTargetTime) {
        uint32_t delayTime = (uint32_t)((frameTargetTime - frameDuration) * 1000.0);
        SDL_Delay(delayTime);
    }
}
double LoopTimer::getLag() const {
    return elapsedTime - elapsedFixedTime;
}
