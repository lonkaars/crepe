

#include "Image_asset.h"
#include "resource_manager.h"
#include "spritesheet.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <cstddef>

int main() {
	SDL_Init(SDL_INIT_VIDEO);

	bool quit = false;

	SDL_Event event;

	SDL_Window * window
		= SDL_CreateWindow("Tessting resources", SDL_WINDOWPOS_UNDEFINED,
						   SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);


	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	ResourceManager * rm = new ResourceManager();

	Texture* img = rm->Load<Texture>("../img.png");
	img->setTexture(*renderer);

	SpriteSheet* SS = rm->Load<SpriteSheet>("../spritesheet_test.png");

	SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
	SDL_RenderClear(renderer);

	while (!quit) {

		while (SDL_PollEvent(&event) != NULL) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}
		}


		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, img->getTexture(), NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
