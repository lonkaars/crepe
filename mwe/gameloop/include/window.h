#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "gameObject.h"
#include <iostream>
class WindowManager{
	public:
		WindowManager();
		virtual ~WindowManager();
		void render(std::vector<GameObject*> objects);
		bool initWindow();
		void destroyWindow();
		
		SDL_Renderer* getRenderer();
	private:
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 600;
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
};
