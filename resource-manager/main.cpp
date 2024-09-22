

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
	ResourceManager * rm = new ResourceManager;

	//Image* img = rm->Load<Image>("../spritesheet_test.png");
	//Resource* sound = rm->Load("/sound.ogg");

	bool quit = false;

	SDL_Event event;

	SDL_Window * window
		= SDL_CreateWindow("Tessting resources", SDL_WINDOWPOS_UNDEFINED,
						   SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	SpriteSheet spritesheet("../spritesheet_test.png", *renderer, 1, 4);
	SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
	SDL_RenderClear(renderer);

	while (!quit) {
		Uint32 ticks = SDL_GetTicks();
		int sprite = (ticks / 100) % 4;

		//SDL_Rect srcrect = { sprite * 32, 0, 32, 64 };
		SDL_Rect dstrect = {10, 10, 32, 64};

		while (SDL_PollEvent(&event) != NULL) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		SDL_RenderClear(renderer);
		spritesheet.select_sprite(sprite, 0);
		spritesheet.draw_selected_sprite(renderer, &dstrect);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
