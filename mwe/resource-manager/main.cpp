

#include "Image_asset.h"
#include "map_asset.h"
#include "resource_converter.h"
#include "resource_manager.h"
#include "spritesheet.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_events.h>
#include <SDL_rect.h>
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

	SDL_Window * window = SDL_CreateWindow(
		"Tessting resources", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0
	);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	ResourceManager * rm = ResourceManager::get_instance();
	ResourceConverter resource_converter;

	Texture * img = rm->Load<Texture>("../img.png");

	SpriteSheet * SS = rm->Load<SpriteSheet>("../spritesheet_test.png");
	Map * map = rm->Load<Map>("../../asset/tiled/demo.tmx");

	SDL_Surface * surface = resource_converter.FromStringToImage(*img);
	SDL_Texture * m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	TiledMap testingTiledMap = resource_converter.FromStringToMap(*map);
	testingTiledMap.SetRenderer(*renderer);

	SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
	SDL_RenderClear(renderer);

	while (!quit) {
		Uint32 ticks = SDL_GetTicks();
		int sprite = (ticks / 100) % 4;

		while (SDL_PollEvent(&event) != NULL) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, m_texture, NULL, NULL);
		testingTiledMap.draw();

		SDL_RenderPresent(renderer);
	}
	delete rm;

	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
