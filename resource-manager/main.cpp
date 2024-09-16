

#include "Image_asset.h"
#include "resource_manager.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <cstddef>


int main(){
	SDL_Init(SDL_INIT_VIDEO);
	ResourceManager* rm = new ResourceManager;


	Image* img = static_cast<Image*>(rm->Load("../img.png"));
	//Resource* sound = rm->Load("/sound.ogg");

	
	bool quit = false;
	
	SDL_Event event;

	SDL_Window* window = SDL_CreateWindow("Tessting resources", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img->surface);


	while (!quit) {
		SDL_WaitEvent(&event);

		switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
		}

		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();



	return 0;
}
