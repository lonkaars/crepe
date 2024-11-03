#pragma once
#include "gameObject.h"
#include "window.h"
#include <SDL2/SDL.h>
class LoopManager {
public:
	LoopManager();
	~LoopManager();
	void setup();
	void loop();

private:
	std::vector<GameObject *> objectList;
	void processInput();
	void update();
	void lateUpdate();
	void fixedUpdate();
	void render();
	bool gameRunning = false;
	WindowManager* window;
	int timeScale = 1;
	float accumulator = 0.0;
	double currentTime;
	double t = 0.0;
	double dt = 0.01;
};
