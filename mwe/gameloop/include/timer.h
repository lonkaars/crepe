#pragma once

#include <SDL2/SDL.h>

class LoopTimer {
public:
    static LoopTimer& getInstance();
    void start();
    void update();
    double getDeltaTime() const;
    int getCurrentTime() const;
	void advanceFixedUpdate();
	double getFixedDeltaTime() const;
    void setFPS(int FPS);
    int getFPS() const;
	double getGameScale();
	void setGameScale(double);
    void enforceFrameRate();
	double getLag() const;
private:
    LoopTimer();
	int FPS = 50;
	double gameScale = 1;
	double maximumDeltaTime = 0.25;
    double deltaTime;
	double frameTargetTime = FPS / 1000;
    double fixedDeltaTime = 0.01;
    double elapsedTime;
    double elapsedFixedTime;
	double time;
    uint64_t lastFrameTime;
};
