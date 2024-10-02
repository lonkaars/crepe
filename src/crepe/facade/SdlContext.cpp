

#include "SdlContext.h"
#include "SDL_rect.h"
#include "api/spritesheet.h"
#include "facade/Texture.h"
#include "util/log.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <iterator>
#include <ostream>

using namespace crepe;


SdlContext& SdlContext::get_instance(){
	static SdlContext instance;
	return instance;
}


SdlContext::SdlContext(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    m_game_window = SDL_CreateWindow("Crepe Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!m_game_window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    m_game_renderer = SDL_CreateRenderer(m_game_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_game_renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_game_window);
        return;
    }
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
            }
}

SdlContext::~SdlContext(){
	if(m_game_renderer)
		SDL_DestroyRenderer(m_game_renderer);

	if (m_game_window) {
		SDL_DestroyWindow(m_game_window);
	}
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* SdlContext::setTextureFromPath(const char* path, SDL_Rect& clip, const int row, const int col){
	dbg_trace();
	
	SDL_Surface* tmp = IMG_Load(path);
	if (!tmp) {
		std::cerr << "Error surface " << IMG_GetError << std::endl;
	}

	clip.w = tmp->w / col;	
	clip.h = tmp->h / row;	

	SDL_Texture* CreatedTexture = SDL_CreateTextureFromSurface(m_game_renderer, tmp);

	if (!CreatedTexture) {
		std::cerr << "Error could not create texture " << IMG_GetError << std::endl;
	}
	SDL_FreeSurface(tmp);

	return CreatedTexture;
}

SDL_Texture* SdlContext::setTextureFromPath(const char* path){
	dbg_trace();
	
	SDL_Surface* tmp = IMG_Load(path);
	if (!tmp) {
		std::cerr << "Error surface " << IMG_GetError << std::endl;
	}
	SDL_Texture* CreatedTexture = SDL_CreateTextureFromSurface(m_game_renderer, tmp);

	if (!CreatedTexture) {
		std::cerr << "Error could not create texture " << IMG_GetError << std::endl;
	}
	SDL_FreeSurface(tmp);

	return CreatedTexture;
}


void SdlContext::loop(const Texture& texture, api::Spritesheet& ss){
	SDL_RenderClear(m_game_renderer);
	bool quit = false;
	SDL_Event event;

	while (!quit) {
		Uint32 ticks = SDL_GetTicks();
		int sprite = (ticks / 100) % 4;
		ss.select_sprite(sprite, 0);

		while (SDL_PollEvent(&event) != NULL) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}

		}

		SDL_RenderClear(m_game_renderer);
		SDL_RenderCopy(m_game_renderer, texture.get_texture(), NULL, NULL);
		ss.draw_selected_sprite(10, 10);
		SDL_RenderPresent(m_game_renderer);
	}
}


