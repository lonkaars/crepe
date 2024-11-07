#include <iostream>

#include "SDLApp.h"

SDLApp::SDLApp(int window_width, int window_height)
	: window_width(window_width), window_height(window_height), window(nullptr),
	  renderer(nullptr) {}

// FIXME: why is there clean_up and ~SDLApp?
SDLApp::~SDLApp() { clean_up(); }

bool SDLApp::initialize() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		// FIXME: throw exception
		std::cerr << "SDL Initialization Error: " << SDL_GetError()
				  << std::endl;
		return false;
	}

	window = SDL_CreateWindow("Particle System", SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED, window_width,
							  window_height, SDL_WINDOW_SHOWN);
	if (!window) {
		// FIXME: throw exception
		std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		// FIXME: throw exception
		std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void SDLApp::handle_events(bool & running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
}

void SDLApp::clear_screen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void SDLApp::present_screen() { SDL_RenderPresent(renderer); }

void SDLApp::draw_square(int x, int y, int size) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = {x, y, size, size};
	SDL_RenderFillRect(renderer, &rect);
}

SDL_Texture * square_texture = nullptr; // Load this with an image or create it

void SDLApp::clean_up() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}
