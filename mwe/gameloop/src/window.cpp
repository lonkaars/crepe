#include "window.h"
WindowManager::WindowManager() {
	if (!initWindow()) {
		printf("Failed to initialize!\n");
	}
}
WindowManager::~WindowManager() { destroyWindow(); }
SDL_Renderer * WindowManager::getRenderer() { return renderer; }

void WindowManager::render(std::vector<GameObject *> objects) {
	// Set the draw color to black and clear the screen
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Print object position (optional for debugging)
	//fprintf(stderr, "%d\n", objectList.size());
	for (int i = 0; i < objects.size(); i++) {
		//fprintf(stderr, "%f\n", objectList[i]->getX());
		// Create a rectangle representing the ball
		SDL_Rect ball_rect = {
			(int) objects[i]->getX(),
			(int) objects[i]->getY(),
			(int) objects[i]->getWidth(),
			(int) objects[i]->getHeight(),
		};
		// Set the draw color to white and render the ball
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &ball_rect);
	}

	SDL_RenderPresent(renderer);
}

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
