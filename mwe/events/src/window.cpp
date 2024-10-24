#include "window.h"
WindowManager::WindowManager() {
}
WindowManager::~WindowManager() { destroyWindow(); }
SDL_Renderer * WindowManager::getRenderer() { return renderer; }

bool WindowManager::initWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error inititalising SDL.\n");
		return false;
	}
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
							  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		fprintf(stderr, "Error creating SDL Window. \n");
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer. \n");
		return false;
	}
	return true;
}
void WindowManager::destroyWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
