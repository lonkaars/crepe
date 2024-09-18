#pragma once
#include <SDL2/SDL.h>
#include "window.h"
#include "gameObject.h"
class LoopManager{
	public:
		LoopManager();
		void setup();
		void loop();
	private:
		
		std::vector<GameObject*> objectList;
		void processInput();
		void update();
		void lateUpdate();
		void fixedUpdate();
		void render();
		bool gameRunning = false;
		WindowManager window;
		int timeScale = 1;
		float lag = 0.0;
		double currentTime;
		double t = 0.0;
		double dt = 0.01;
		state previous;
};
