#pragma once

#include <SDL2/SDL.h>

#include "api/ParticleEmitter.h"

class SDLApp {
public:
	SDLApp(int window_width, int window_height);
	~SDLApp();

	bool initialize();
	void handle_events(bool & running);
	void clear_screen();
	void present_screen();
	void draw_square(int x, int y, int size);
	void clean_up();
	void draw_particles(const std::vector<crepe::ParticleEmitter> & emitters);
	void draw_multiple_squares(const std::vector<SDL_Rect> & squares);

private:
	int window_width;
	int window_height;
	SDL_Window * window;
	SDL_Renderer * renderer;
};
