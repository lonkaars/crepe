#pragma once
#include "timer.h"
#include "window.h"
#include <SDL2/SDL.h>
//#include "combinedEvent.h"
#include "eventHandler.h"
#include "eventManager.h"
#include "loopManager.h"
class LoopManager {
public:
	LoopManager();
	void setup();
	void loop();
	void setRunning(bool running);

private:
	void processInput();
	void update();
	void lateUpdate();
	void fixedUpdate();
	void render();
	bool gameRunning = false;
	WindowManager window;
	int timeScale = 1;
	float accumulator = 0.0;
	double currentTime;
	double t = 0.0;
	double dt = 0.01;
};
