#pragma once

#include <SDL2/SDL.h>

class LoopTimer {
public:
    static LoopTimer& getInstance();
    void start();
    void update();
    float getDeltaTime() const;
	float getDeltaTimeMs() const;
	float getFixedDeltaTime() const;
    int getCurrentTime() const;
    void setFPS(int FPS);
    int getFPS() const;
    void enforceFrameRate();
	float getLag() const;
private:
    LoopTimer();
	int FPS = 30;
	float frameTargetTime = FPS / 1000;
    int lastTime;
	float fixedDeltaTime = 2;
	float maxDeltaTime = 1;
	float fixedTime = 0;
    int lastFrameTime;
    float deltaTime;
	float time = 0;
    int frequency;
	float lag;
};
