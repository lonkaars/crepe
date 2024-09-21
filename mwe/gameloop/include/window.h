#pragma once
#include "gameObject.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
class WindowManager {
public:
	WindowManager();
	virtual ~WindowManager();
	void render(std::vector<GameObject *> objects);
	bool initWindow();
	void destroyWindow();

	SDL_Renderer * getRenderer();

private:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
};
