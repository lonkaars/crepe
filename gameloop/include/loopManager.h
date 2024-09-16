#pragma once
#include <SDL2/SDL.h>
#include "window.h"
class LoopManager{
	public:
		LoopManager();
		void setup();
		void loop();
	private:
		
		
		void processInput();
		void update();
		void render();
		bool gameRunning;
		WindowManager window;

};
